# Baba Is Agent
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://github.com/JYPark09/BabaIsAgent/blob/master/LICENSE)
[![Build Status](https://travis-ci.com/JYPark09/BabaIsAgent.svg?branch=master)](https://travis-ci.com/JYPark09/BabaIsAgent)
[![Build status](https://ci.appveyor.com/api/projects/status/x3cs2pyati2t6a2s/branch/master?svg=true)](https://ci.appveyor.com/project/JYPark09/babaisyou/branch/master)  
[![CodeFactor](https://www.codefactor.io/repository/github/jypark09/babaisagent/badge)](https://www.codefactor.io/repository/github/jypark09/babaisagent)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/615531ce885443ec981e7aee0b6388de)](https://www.codacy.com/app/JYPark09/BabaIsAgent?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=JYPark09/BabaIsAgent&amp;utm_campaign=Badge_Grade)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/JYPark09/BabaIsAgent.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/JYPark09/BabaIsAgent/alerts/)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/JYPark09/BabaIsAgent.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/JYPark09/BabaIsAgent/context:cpp)  
BabaIsAgent is [Baba Is You](https://store.steampowered.com/app/736260/Baba_Is_You/) simulation for Reinforcement Learning.  
This project is a research project at [OOPArts](https://www.facebook.com/OOPArts-%EC%98%A4%ED%8C%8C%EC%B8%A0-1232318310248618/).

## Key Features
- C++17 based Baba Is You library
- GUI simulator program

## To-do Features
- [ ] Game simulation
- [ ] Level solver

## Quick Start
First, clone the repository:
```
git clone --recursive https://github.com/JYPark09/BabaIsAgent
cd BabaIsAgent
```

Second, build project.

### Linux, macOS, Windows Subsystem for Linux(WSL)
```
mkdir build
cd build
cmake ..
make
```

### Windows
```
mkdir build
cd build
cmake .. -G"Visual Studio 16 2019" -A x64
MSBuild BabaIsAgent.sln /p:Configuration=Release
```

## Contact
You can contact us using the following means.
- e-mail: jyp10987 at gmail.com
- [Facebook](https://www.facebook.com/OOPArts-%EC%98%A4%ED%8C%8C%EC%B8%A0-1232318310248618/)
- github issue

## License
This project is based on [GNU General Public License v3](https://opensource.org/licenses/GPL-3.0).  
Copyright(C) 2019 BabaIsAgent Team
- [Junyeong Park](https://github.com/JYPark09)
- [Hyeonsu Kim](https://github.com/git-rla)