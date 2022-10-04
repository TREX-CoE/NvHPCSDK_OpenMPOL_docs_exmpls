# NVidia HPC SDK + OpenMP Offload Docs & Examples
Collection of tutorials and examples on OpenMP offloading of data and computations on Nvidia GPUs using the Nvidia HPC SDK

Here you will find a set of minimal working examples (MWEs) that were useful to me whilst figuring out how to use OpenMP offloading of data and computations to an Nvidia GPU. For now it only containes three MWEs:

- Basic use of a DGEMM using cuBLAS
- Matrix inversion using cuSOLVER
- Matrix determinant using cuSOLVER

All the MWEs are independent and have their own build script. Only the NVidia HPC SDK is required and initialised using the provided Environment Modules scripts in '$NVHPC/modulefiles/nvhpc'. You can download it here:
https://developer.nvidia.com/nvidia-hpc-sdk-downloads

Other useful examples on how to initialize and use CUDA math libraries can be found here:
https://github.com/NVIDIA/CUDALibrarySamples

To get started with OpenMP ofloading I was relying heavily on talks and tutorials I found on the web. A few notables ones are

- A talk by Jeff Larkin and Tim Costa from NVIDIA on best practices for OpenMP on NVIDIA gpus: https://youtu.be/9w_2tj2uD4M
- NVidia HPC SDK Training, Jan 2022: https://www.youtube.com/playlist?list=PL20S5EeApOSulLcgvbluJB-gJjls7yCsk
  Session NR 6 & 7 are especially useful for getting to know and use NSight Systems & Compute to visuallize what is going on on your CPU and GPU in terms of data transfers and synchrinisation, and execution of kernels.
- Introduction to OpenMP Device Offload, Oak Ridge/NERSC , Sept 22-23, 2021: https://www.nersc.gov/users/training/events/openmp-device-offload-sept-2021/|
  - Day 1 slides: https://www.olcf.ornl.gov/wp-content/uploads/2021/08/ITOpenMP_Day1.pdf
  - Day2 slides: https://www.olcf.ornl.gov/wp-content/uploads/2021/08/ITOpenMPO_Day2.pdf
  
Blue Waters Webinars:
---------------------
Introduction to NVIDIA Nsight Systems
    https://www.youtube.com/watch?v=WA8C48FJi3c
Introduction to NVIDIA Nsight Compute
    https://www.youtube.com/watch?v=nYSdsJE2zMs&t=1296s



I encourage everyone who is interested in developing code for GPUs to contribute useful documentation, tutorials, best practices and MWEs.
In case of MWEs, please keep them as 'minimal' as possible! Only the essentials, no unnecessary boilerplate code.
