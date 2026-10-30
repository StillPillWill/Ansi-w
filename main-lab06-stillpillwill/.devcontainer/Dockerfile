# Base image is old because it's unfortunately the most recent available on Gradescope
FROM mcr.microsoft.com/devcontainers/cpp:ubuntu-22.04

# Clang uses GCC's standard library, and Ubuntu 22.04's (GCC 11) lacks parts of
# C++20 such as <format>. Clang picks the newest one installed, so this one is
# used without any flag. Keep the same version as in the Gradescope image.
#
# software-properties-common provides add-apt-repository, which the base image
# lacks.
RUN apt-get update \
 && apt-get install -y --no-install-recommends software-properties-common \
 && add-apt-repository -y ppa:ubuntu-toolchain-r/test \
 && apt-get install -y --no-install-recommends libstdc++-14-dev \
 && rm -rf /var/lib/apt/lists/*
