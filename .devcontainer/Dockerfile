ARG VARIANT="ubuntu"
FROM mcr.microsoft.com/devcontainers/base:${VARIANT}

# Install build tools and valgrind (as root)
RUN sudo apt-get update && \
    sudo apt-get install -y build-essential valgrind curl git && \
    sudo apt-get clean && \
    sudo rm -rf /var/lib/apt/lists/*

# Homebrew does not run as root, so execute it as the vscode user.
USER vscode
WORKDIR /home/vscode

# Install Homebrew and readline in the same RUN (to ensure brew is available)
RUN NONINTERACTIVE=1 /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)" && \
    eval "$(/home/linuxbrew/.linuxbrew/bin/brew shellenv)" && \
    brew install readline && \
    echo 'eval "$(/home/linuxbrew/.linuxbrew/bin/brew shellenv)"' >> ~/.bashrc