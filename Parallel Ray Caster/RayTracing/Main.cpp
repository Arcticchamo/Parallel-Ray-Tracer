#define clew_STATIC
#include <clew\clew.h>
#include <glm\glm\glm.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>

#include "Colour.h"
#include "lodepng.h"
#include "Math.h"
#include "Ray.h"
#include "Sphere.h"
#include "Vector3.h"

const int Width = 1920;
const int Height = 1080;

Colour Blend(Colour _a, Colour _b)
{
	Colour result;

	float a1 = _a.A / 255.0f;
	float a2 = _b.A / 255.0f;

	result.R = (a1 * _a.R + a2 * (1 - a1) * _b.R);
	result.G = (a1 * _a.G + a2 * (1 - a1) * _b.G);
	result.B = (a1 * _a.B + a2 * (1 - a1) * _b.B);
	result.A = (255 * (a1 + a1 * (1 - a1)));

	return result;
}

int main(int argc, char* argv[])
{
	std::vector<Colour> pixel_colour;

	const std::string FILE_NAME = "image1.png";

	Colour black(0.0f, 0.0f, 0.0f, 255);

	for (int i = 0; i < Height * Width; i++)
	{
		pixel_colour.push_back(black);
	}

	bool clPresent = 0 == clewInit();
	if (!clPresent)
	{
		throw std::runtime_error("OpenCL Library not found!");
	}

	cl_platform_id platform;

	clGetPlatformIDs(1, &platform, NULL);

	cl_device_id device;

	clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);

	cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
	cl_command_queue queue = clCreateCommandQueue(context, device, 0, NULL); 
	std::ifstream file("Assets/kernel.txt");

	std::string source;

	while (!file.eof()) 
	{
		char line[256];
		file.getline(line, 255);
		source += line;
		source += "\n";
	}
	const char* str = source.c_str();

	cl_program program = clCreateProgramWithSource(context, 1, &str, NULL, NULL);
	cl_int result = clBuildProgram(program, 1, &device, NULL, NULL, NULL);

	if (result) 
	{
		std::cout << "Error during compilation! (" << result << ")" << std::endl;
		// Determine the size of the log
		size_t log_size;
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

		// Allocate memory for the log
		char *log = (char *)malloc(log_size);

		// Get the log
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

		// Print the log
		printf("%s\n", log);
	}
	else
	{
		std::cout << "No Error During Compilation!" << std::endl;
	}
	
	cl_kernel kernel = clCreateKernel(program, "main", NULL);

	cl_mem output = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(cl_float4) * (Width * Height), NULL, 0); //Colour of Current Pixel

	clSetKernelArg(kernel, 0, sizeof(output), (void*)&output);

	size_t global_work_size = Height * Width;
	int p = 0;
	unsigned char* pixeldata = new unsigned char[Width * Height * 4];

	#pragma omp parallel
	{
		clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_work_size, NULL, 0, NULL, NULL);
		cl_float4 *resultBufferPtr = (cl_float4*)clEnqueueMapBuffer(queue, output, CL_TRUE, CL_MAP_READ, 0, sizeof(cl_float4) * Height * Width, 0, NULL, NULL, NULL);


		#pragma omp for
		{
			for (int i = 0; i < Height * Width; i++)
			{
				pixeldata[i * 4 + 0] = (unsigned char)resultBufferPtr[i].x;
				pixeldata[i * 4 + 1] = (unsigned char)resultBufferPtr[i].y;
				pixeldata[i * 4 + 2] = (unsigned char)resultBufferPtr[i].z;
				pixeldata[i * 4 + 3] = (unsigned char)resultBufferPtr[i].w;
			}
		}
		

	}

	unsigned int error = lodepng::encode(FILE_NAME, pixeldata, Width, Height);

	if (error)
	{
	std::cout << "Error, PNG Encoder error: " << error << ": " << lodepng_error_text(error) << std::endl;
	}

	delete[] pixeldata;


	return 0;
}
