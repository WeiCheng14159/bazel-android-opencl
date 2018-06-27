/* Copyright 1993-2009 NVIDIA Corporation.  All rights reserved.
   Modified by Mark Zwolinski, December 2009
   Modified by Robert McGibbon, August 2013
   Modified by Cheng Wei, November 2017
*/

#include "CL/cl.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sstream>
#include <fstream>

void clPrintDevInfo(cl_device_id device) {
  char device_string[1024];

  // CL_DEVICE_NAME
  clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(device_string), &device_string, NULL);
  printf("  CL_DEVICE_NAME: \t\t\t%s\n", device_string);

  // CL_DEVICE_VENDOR
  clGetDeviceInfo(device, CL_DEVICE_VENDOR, sizeof(device_string), &device_string, NULL);
  printf("  CL_DEVICE_VENDOR: \t\t\t%s\n", device_string);

  // CL_DRIVER_VERSION
  clGetDeviceInfo(device, CL_DRIVER_VERSION, sizeof(device_string), &device_string, NULL);
  printf("  CL_DRIVER_VERSION: \t\t\t%s\n", device_string);

  // CL_DEVICE_INFO
  cl_device_type type;
  clGetDeviceInfo(device, CL_DEVICE_TYPE, sizeof(type), &type, NULL);
  if( type & CL_DEVICE_TYPE_CPU )
    printf("  CL_DEVICE_TYPE:\t\t\t%s\n", "CL_DEVICE_TYPE_CPU");
  if( type & CL_DEVICE_TYPE_GPU )
    printf("  CL_DEVICE_TYPE:\t\t\t%s\n", "CL_DEVICE_TYPE_GPU");
  if( type & CL_DEVICE_TYPE_ACCELERATOR )
    printf("  CL_DEVICE_TYPE:\t\t\t%s\n", "CL_DEVICE_TYPE_ACCELERATOR");
  if( type & CL_DEVICE_TYPE_DEFAULT )
    printf("  CL_DEVICE_TYPE:\t\t\t%s\n", "CL_DEVICE_TYPE_DEFAULT");

  // CL_DEVICE_MAX_COMPUTE_UNITS
  cl_uint compute_units;
  clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(compute_units), &compute_units, NULL);
  printf("  CL_DEVICE_MAX_COMPUTE_UNITS:\t\t%u\n", compute_units);

  // CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS
  size_t workitem_dims;
  clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(workitem_dims), &workitem_dims, NULL);
  printf("  CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS:\t%u\n", workitem_dims);

  // CL_DEVICE_MAX_WORK_ITEM_SIZES
  size_t workitem_size[3];
  clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(workitem_size), &workitem_size, NULL);
  printf("  CL_DEVICE_MAX_WORK_ITEM_SIZES:\t%u / %u / %u \n", workitem_size[0], workitem_size[1], workitem_size[2]);

  // CL_DEVICE_MAX_WORK_GROUP_SIZE
  size_t workgroup_size;
  clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(workgroup_size), &workgroup_size, NULL);
  printf("  CL_DEVICE_MAX_WORK_GROUP_SIZE:\t%u\n", workgroup_size);

  // CL_DEVICE_MAX_CLOCK_FREQUENCY
  cl_uint clock_frequency;
  clGetDeviceInfo(device, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(clock_frequency), &clock_frequency, NULL);
  printf("  CL_DEVICE_MAX_CLOCK_FREQUENCY:\t%u MHz\n", clock_frequency);

  // CL_DEVICE_ADDRESS_BITS
  cl_uint addr_bits;
  clGetDeviceInfo(device, CL_DEVICE_ADDRESS_BITS, sizeof(addr_bits), &addr_bits, NULL);
  printf("  CL_DEVICE_ADDRESS_BITS:\t\t%u\n", addr_bits);

  // CL_DEVICE_MAX_MEM_ALLOC_SIZE
  cl_ulong max_mem_alloc_size;
  clGetDeviceInfo(device, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(max_mem_alloc_size), &max_mem_alloc_size, NULL);
  printf("  CL_DEVICE_MAX_MEM_ALLOC_SIZE:\t\t%u MByte\n", (unsigned int)(max_mem_alloc_size / (1024 * 1024)));

  // CL_DEVICE_GLOBAL_MEM_SIZE
  cl_ulong mem_size;
  clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(mem_size), &mem_size, NULL);
  printf("  CL_DEVICE_GLOBAL_MEM_SIZE:\t\t%u MByte\n", (unsigned int)(mem_size / (1024*1024)));

  // CL_DEVICE_GLOBAL_MEM_CACHE_TYPE
  cl_device_mem_cache_type global_mem_type;
  clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHE_TYPE, sizeof(global_mem_type), &global_mem_type, NULL);
  if ( global_mem_type == CL_NONE )
    printf("  CL_DEVICE_GLOBAL_MEM_CACHE_TYPE:      CL_NONE\n" );
  else if( global_mem_type == CL_READ_ONLY_CACHE )
    printf("  CL_DEVICE_GLOBAL_MEM_CACHE_TYPE:      CL_READ_ONLY_CACHE\n" );
  else if( global_mem_type == CL_READ_WRITE_CACHE )
    printf("  CL_DEVICE_GLOBAL_MEM_CACHE_TYPE:      CL_READ_WRITE_CACHE\n" );

  // CL_DEVICE_GLOBAL_MEM_CACHE_SIZE
  cl_ulong global_mem_cache_size;
  clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, sizeof(global_mem_cache_size), &global_mem_cache_size, NULL);
  printf("  CL_DEVICE_GLOBAL_MEM_CACHE_SIZE:      %u KByte\n", (unsigned int)(global_mem_cache_size)/(1024));

  // CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE
  cl_uint mem_cacheline_size;
  clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE, sizeof(mem_cacheline_size), &mem_cacheline_size, NULL);
  printf("  CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE:  %u Byte\n", (unsigned int)(mem_cacheline_size));

  // CL_DEVICE_ERROR_CORRECTION_SUPPORT
  cl_bool error_correction_support;
  clGetDeviceInfo(device, CL_DEVICE_ERROR_CORRECTION_SUPPORT, sizeof(error_correction_support), &error_correction_support, NULL);
  printf("  CL_DEVICE_ERROR_CORRECTION_SUPPORT:\t%s\n", error_correction_support == CL_TRUE ? "yes" : "no");

  // CL_DEVICE_LOCAL_MEM_TYPE
  cl_device_local_mem_type local_mem_type;
  clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_TYPE, sizeof(local_mem_type), &local_mem_type, NULL);
  printf("  CL_DEVICE_LOCAL_MEM_TYPE:\t\t%s\n", local_mem_type == 1 ? "local" : "global");

  // CL_DEVICE_LOCAL_MEM_SIZE
  clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(mem_size), &mem_size, NULL);
  printf("  CL_DEVICE_LOCAL_MEM_SIZE:\t\t%u KByte\n", (unsigned int)(mem_size / 1024));

  // CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE
  clGetDeviceInfo(device, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, sizeof(mem_size), &mem_size, NULL);
  printf("  CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE:\t%u KByte\n", (unsigned int)(mem_size / 1024));

  // CL_DEVICE_QUEUE_PROPERTIES
  cl_command_queue_properties queue_properties;
  clGetDeviceInfo(device, CL_DEVICE_QUEUE_PROPERTIES, sizeof(queue_properties), &queue_properties, NULL);
  if( queue_properties & CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE )
    printf("  CL_DEVICE_QUEUE_PROPERTIES:\t\t%s\n", "CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE");
  if( queue_properties & CL_QUEUE_PROFILING_ENABLE )
    printf("  CL_DEVICE_QUEUE_PROPERTIES:\t\t%s\n", "CL_QUEUE_PROFILING_ENABLE");

  // CL_DEVICE_IMAGE_SUPPORT
  cl_bool image_support;
  clGetDeviceInfo(device, CL_DEVICE_IMAGE_SUPPORT, sizeof(image_support), &image_support, NULL);
  printf("  CL_DEVICE_IMAGE_SUPPORT:\t\t%u\n", image_support);

  // CL_DEVICE_MAX_READ_IMAGE_ARGS
  cl_uint max_read_image_args;
  clGetDeviceInfo(device, CL_DEVICE_MAX_READ_IMAGE_ARGS, sizeof(max_read_image_args), &max_read_image_args, NULL);
  printf("  CL_DEVICE_MAX_READ_IMAGE_ARGS:\t%u\n", max_read_image_args);

  // CL_DEVICE_MAX_WRITE_IMAGE_ARGS
  cl_uint max_write_image_args;
  clGetDeviceInfo(device, CL_DEVICE_MAX_WRITE_IMAGE_ARGS, sizeof(max_write_image_args), &max_write_image_args, NULL);
  printf("  CL_DEVICE_MAX_WRITE_IMAGE_ARGS:\t%u\n", max_write_image_args);

  // CL_DEVICE_IMAGE2D_MAX_WIDTH, CL_DEVICE_IMAGE2D_MAX_HEIGHT, CL_DEVICE_IMAGE3D_MAX_WIDTH, CL_DEVICE_IMAGE3D_MAX_HEIGHT, CL_DEVICE_IMAGE3D_MAX_DEPTH
  size_t szMaxDims[5];
  printf("\n  CL_DEVICE_IMAGE <dim>");
  clGetDeviceInfo(device, CL_DEVICE_IMAGE2D_MAX_WIDTH, sizeof(size_t), &szMaxDims[0], NULL);
  printf("\t\t\t2D_MAX_WIDTH\t %u\n", szMaxDims[0]);
  clGetDeviceInfo(device, CL_DEVICE_IMAGE2D_MAX_HEIGHT, sizeof(size_t), &szMaxDims[1], NULL);
  printf("\t\t\t\t\t2D_MAX_HEIGHT\t %u\n", szMaxDims[1]);
  clGetDeviceInfo(device, CL_DEVICE_IMAGE3D_MAX_WIDTH, sizeof(size_t), &szMaxDims[2], NULL);
  printf("\t\t\t\t\t3D_MAX_WIDTH\t %u\n", szMaxDims[2]);
  clGetDeviceInfo(device, CL_DEVICE_IMAGE3D_MAX_HEIGHT, sizeof(size_t), &szMaxDims[3], NULL);
  printf("\t\t\t\t\t3D_MAX_HEIGHT\t %u\n", szMaxDims[3]);
  clGetDeviceInfo(device, CL_DEVICE_IMAGE3D_MAX_DEPTH, sizeof(size_t), &szMaxDims[4], NULL);
  printf("\t\t\t\t\t3D_MAX_DEPTH\t %u\n", szMaxDims[4]);

  // CL_DEVICE_PREFERRED_VECTOR_WIDTH_<type>
  printf("  CL_DEVICE_PREFERRED_VECTOR_WIDTH_<t>\t");
  cl_uint vec_width [6];
  clGetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR, sizeof(cl_uint), &vec_width[0], NULL);
  clGetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT, sizeof(cl_uint), &vec_width[1], NULL);
  clGetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT, sizeof(cl_uint), &vec_width[2], NULL);
  clGetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG, sizeof(cl_uint), &vec_width[3], NULL);
  clGetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT, sizeof(cl_uint), &vec_width[4], NULL);
  clGetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE, sizeof(cl_uint), &vec_width[5], NULL);
  printf("CHAR %u, SHORT %u, INT %u, FLOAT %u, DOUBLE %u\n",
   vec_width[0], vec_width[1], vec_width[2], vec_width[3], vec_width[4]);

  //CL_DEVICE_SVM_CAPABILITIES
  cl_device_svm_capabilities svm_cap;
  clGetDeviceInfo(device, CL_DEVICE_SVM_CAPABILITIES, sizeof(svm_cap), &svm_cap, NULL);

  char svm_cap_string[1024] = "";

  if( svm_cap == CL_DEVICE_SVM_COARSE_GRAIN_BUFFER )
      strcpy(svm_cap_string, "CL_DEVICE_SVM_COARSE_GRAIN_BUFFER");
  else if(svm_cap == CL_DEVICE_SVM_FINE_GRAIN_BUFFER )
      strcpy(svm_cap_string, "CL_DEVICE_SVM_FINE_GRAIN_BUFFER");
  else if(svm_cap == CL_DEVICE_SVM_FINE_GRAIN_SYSTEM )
      strcpy(svm_cap_string, "CL_DEVICE_SVM_FINE_GRAIN_SYSTEM");
  else if(svm_cap == CL_DEVICE_SVM_ATOMICS )
      strcpy(svm_cap_string, "CL_DEVICE_SVM_ATOMICS");
  else
      strcpy(svm_cap_string, "err");
  printf("  CL_DEVICE_SVM_CAPABILITIES: \t%s\n", svm_cap_string);

  printf("\n\n\n");
}

int main(int argc, const char** argv) {
  // start logs
  printf("clDeviceQuery Starting...\n\n");
  bool bPassed = true;
  std::string sProfileString = "clDeviceQuery, Platform Name = ";

  // Get OpenCL platform ID for NVIDIA if avaiable, otherwise default
  char cBuffer[1024];
  cl_platform_id clSelectedPlatformID = NULL;
  cl_platform_id* clPlatformIDs;

  cl_uint num_platforms;
  cl_int ciErrNum = clGetPlatformIDs(0, NULL, &num_platforms);
  if (ciErrNum != CL_SUCCESS) {
    printf(" Error %i in clGetPlatformIDs Call!\n\n", ciErrNum);
    bPassed = false;
  } else {
    if (num_platforms == 0) {
      printf("No OpenCL platform found!\n\n");
      bPassed = false;
    } else {
      // if there's one platform or more, make space for ID's
      if ((clPlatformIDs = (cl_platform_id*)malloc(num_platforms * sizeof(cl_platform_id))) == NULL) {
	printf("Failed to allocate memory for cl_platform ID's!\n\n");
	bPassed = false;
      }

      printf("%d OpenCL Platforms found\n\n", num_platforms);
      // get platform info for each platform
      ciErrNum = clGetPlatformIDs (num_platforms, clPlatformIDs, NULL);
      for(cl_uint i = 0; i < num_platforms; ++i) {
	ciErrNum = clGetPlatformInfo (clPlatformIDs[i], CL_PLATFORM_NAME, 1024, &cBuffer, NULL);
	if(ciErrNum == CL_SUCCESS) {
	  clSelectedPlatformID = clPlatformIDs[i];
	  // Get OpenCL platform name and version
	  ciErrNum = clGetPlatformInfo (clSelectedPlatformID, CL_PLATFORM_NAME, sizeof(cBuffer), cBuffer, NULL);
	  if (ciErrNum == CL_SUCCESS) {
	    printf(" CL_PLATFORM_NAME: \t%s\n", cBuffer);
	    sProfileString += cBuffer;
	  } else {
	    printf(" Error %i in clGetPlatformInfo Call !!!\n\n", ciErrNum);
    bPassed = false;
  }
  sProfileString += ", Platform Version = ";

  ciErrNum = clGetPlatformInfo (clSelectedPlatformID, CL_PLATFORM_VERSION, sizeof(cBuffer), cBuffer, NULL);
  if (ciErrNum == CL_SUCCESS) {
    printf(" CL_PLATFORM_VERSION: \t%s\n", cBuffer);
    sProfileString += cBuffer;
  } else {
    printf(" Error %i in clGetPlatformInfo Call !!!\n\n", ciErrNum);
    bPassed = false;
  }

  // Log OpenCL SDK Version # (for convenience:  not specific to OpenCL)
  sProfileString += ", NumDevs = ";

  // Get and log OpenCL device info
  cl_uint ciDeviceCount;
  cl_device_id *devices;
  printf("OpenCL Device Info:\n\n");
  ciErrNum = clGetDeviceIDs (clSelectedPlatformID, CL_DEVICE_TYPE_ALL, 0, NULL, &ciDeviceCount);

  // check for 0 devices found or errors...
  if (ciDeviceCount == 0) {
    printf(" No devices found supporting OpenCL (return code %i)\n\n", ciErrNum);
    bPassed = false;
    sProfileString += "0";
  } else if (ciErrNum != CL_SUCCESS) {
    printf(" Error %i in clGetDeviceIDs call !!!\n\n", ciErrNum);
    bPassed = false;
  } else {
    // Get and log the OpenCL device ID's
    ciErrNum = clGetPlatformInfo (clSelectedPlatformID, CL_PLATFORM_NAME, sizeof(cBuffer), cBuffer, NULL);
    printf(" %u devices found supporting OpenCL on: %s\n\n", ciDeviceCount, cBuffer);
    char cTemp[2];
    sprintf(cTemp, "%u", ciDeviceCount);
    sProfileString += cTemp;
    if ((devices = (cl_device_id*)malloc(sizeof(cl_device_id) * ciDeviceCount)) == NULL) {
      printf(" Failed to allocate memory for devices !!!\n\n");
      bPassed = false;
    }
    ciErrNum = clGetDeviceIDs (clSelectedPlatformID, CL_DEVICE_TYPE_ALL, ciDeviceCount, devices, &ciDeviceCount);
    if (ciErrNum == CL_SUCCESS) {
      for(unsigned int i = 0; i < ciDeviceCount; ++i )  {
        printf(" ----------------------------------\n");
clGetDeviceInfo(devices[i], CL_DEVICE_NAME, sizeof(cBuffer), &cBuffer, NULL);
printf(" Device %s\n", cBuffer);
printf(" ---------------------------------\n");
clPrintDevInfo(devices[i]);
sProfileString += ", Device = ";
sProfileString += cBuffer;
      }
            } else {
      printf(" Error %i in clGetDeviceIDs call !!!\n\n", ciErrNum);
      bPassed = false;
    }
  }

  // masterlog info
  sProfileString += "\n";
  printf("%s", sProfileString.c_str());
}
free(clPlatformIDs);
      }
    }
  }

  // Log system info(for convenience:  not specific to OpenCL)
  printf( "\nSystem Info: \n\n");
  char timestr[255];
  time_t now = time(NULL);
  struct tm  *ts;

  ts = localtime(&now);

  strftime(timestr, 255, " %H:%M:%S, %m/%d/%Y",ts);

  // write time and date to logs
  printf(" Local Time/Date = %s\n", timestr);
  // write proc and OS info to logs
  // parse /proc/cpuinfo
  std::ifstream cpuinfo( "/proc/cpuinfo" ); // open the file in /proc
  std::string tmp;

  int cpu_num = 0;
  std::string cpu_name = "none";
  do {
    cpuinfo >> tmp;

    if( tmp == "processor" )
      cpu_num++;

    if( tmp == "name" ) {
      cpuinfo >> tmp; // skip :

      std::stringstream tmp_stream("");
      do {
	cpuinfo >> tmp;
	if (tmp != std::string("stepping")) {
	  tmp_stream << tmp.c_str() << " ";
	}

      }
      while (tmp != std::string("stepping"));

      cpu_name = tmp_stream.str();
    }
  }
  while ( (! cpuinfo.eof()) );

  // Linux version
  std::ifstream version( "/proc/version" );
  char versionstr[255];

  version.getline(versionstr, 255);

  printf(" CPU Name: %s\n # of CPU processors: %u\n %s\n\n\n",
	 cpu_name.c_str(),cpu_num,versionstr);

  // finish
  printf("TEST %s\n\n", bPassed ? "PASSED" : "FAILED !!!");
}
