
<a name="readme-top"></a>

<br />
<div align="center">
  <a href="https://github.com/github_username/repo_name">
    <img src="images/banner.png" alt="Logo" width="whatever" height="whatever">
  </a>

<h3 align="center">Nintondo</h3>

  <p align="center">
    powered by students of the University of Trento
    <br />
    <a href="https://docs.google.com/presentation/d/1FjArqNzbcVRavWcu7ZA5t-i7vRcWXR6WLDtwkMczJLI/edit?usp=sharing"><strong>Project presentation»</strong></a>
    <br />
    <a href="https://github.com/chaudhry0/Nintondo/tree/master/Documentazione"><strong>Explore the documentations»</strong></a>
    <br />
    <br />
    <a href="https://www.youtube.com/watch?v=yPBUJ5CSmYQ">View video Demo</a>
    ·
    <a href="https://github.com/chaudhry0/Nintondo/issues">Report Bug</a>
    ·
    <a href="https://github.com/chaudhry0/Nintondo/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
        <li><a href="#developed-games">Developed Games</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#hardware-prerequisites">Hardware Prerequisites</a></li>
        <li><a href="#software-prerequisites">Software Prerequisites</a></li>
        <li><a href="#nintondo-installation">Nintondo Installation</a></li>
      </ul>
    </li>
    <li><a href="#project-layout">Project Layout</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#about-us">About Us</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

[![Boosterpack image][boosterpack]](https://www.ti.com/tool/BOOSTXL-EDUMKII)

Welcome to Nintondo!
your one-stop-shop for all your gaming needs!

Nintondo is a game hub that brings back the classic arcade games with a modern twist. As a tribute to the popular Nintendo console, our project is designed to bring the joy of arcade games to everyone. We have handpicked some of the most popular arcade games and developed them for your entertainment.

In Nintondo, you can choose from a variety of games including snake, pong, space invaders, floppy disk and rhino runner. Each game is unique in its own way and will bring back memories of the classic arcade games. While some of the games are inspired by popular games, they still have their own game modes and rules, so be ready to enjoy a new experience.

The Nintondo project is powered by a microcontroller manufactured by Texas Instruments, ensuring that the games run smoothly and efficiently. The hardware is designed to handle multiple games, so you can switch between games without any interruptions.

We believe that everyone deserves to experience the joy of arcade games, and that's why we have developed Nintondo.

So, grab your controllers and get ready to experience the fun and excitement of Nintondo! We can't wait to see you on the virtual battlefield.

<!-- DEVELOPEDGAMES -->
### Developed Games
- **SNAKE**: the game became famous to be in every smartphone. The goal of the game is to eat as many apples as possible without never hitting your tail or any border. Every time an apple is eaten the snake length increases
- **PONG**: a game that simulates a Ping Pong match. The goal of the game is to not leave the ball hitting your side and to try to win the match
- **RHINO RUNNER**: a funny game inspired to the famous Dino game developed by Google and that happears whenever the connection is down. The goal of this game is to dodge every enemy (cactus and birds)
- **FLOPPY DISK**: a funny game inspired to the Flopppy Bird, a famous smartphone game that became viral some years ago. The main goal is to dodge every RAM bank
- **SPACE INVADERS**: one of the most famous arcade game. The goal of this game is to hit every enemy spawning from the top of the screen with available bullets
- **COIN FLIP**: simple game to challenge fate, great when you have to make important decisions



<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Built With
* [![C][C-logo]][C-url]
* [![CCS][CCS-logo]][CCS-url]
* [![Texas Board][Texas-logo]][Texas-url]
<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

Welcome to Nintondo repository! In order to get started and have a working local copy of Nintondo follow these simple example steps.

### Hardware Prerequisites
#### We have used products manufactured by Texas Instruments Incorporated (TI)
- <a href="https://www.amazon.com/Development-Boards-Kits-MSP432P401R-LaunchPad/dp/B01LWR1MSO">MSP432P401R LaunchPad</a>  (not available on the official site)
- <a href="https://www.ti.com/tool/BOOSTXL-EDUMKII">BOOSTXL-EDUMKII</a>  (Educational BoosterPack MKII)
- <a href="https://a.co/d/8gtmkFi">USB micro b </a> (data cable)

### Software Prerequisites

#### Installing TI CSS and ARM compiler for <a href="https://www.ti.com/product/MSP432P401R">MSP432P401R</a>
- We will use <a href="https://www.ti.com/tool/CCSTUDIO"> Code Composer Studio (CCS) Integrated Development Environment (IDE)</a> from Texas Instruments.

#### Download
- <a href="https://www.ti.com/tool/download/CCSTUDIO">Download TI CSS</a>

#### Installation
Follow the step-by-step installation tutorial from TI:
- <a href="https://software-dl.ti.com/ccs/esd/documents/users_guide_10.1.0/ccs_installation.html">Installation</a>

#### Update
After installation:
  - start TI CSS and create a new workspace
  - update CCS by selecting ARM Compiler Tools and ARM GCC Compiler Tools (You can click on the icon in the bottom right corner).


### Nintondo Installation
1. Clone the repo
   ```sh
   git clone https://github.com/chaudhry0/Nintondo.git
   ```
2. Create a new project with CCS
    -  File->New->CCS Project
    -  Target: MSP432 Family  MSP432P401R
    -  Project name: Nintondo
3. Paste all the content of cloned folder `Nintondo` to your project
4. Adding DriverLib to your project:
    - Extract simplelink_msp432p4_sdk_3_40_01_02.zip file. 
    - Open CSS and left click on Project Folder to select Properties
    - Select CSS Build
    - Click ARM Compiler and then Include Options
      - Add "simplelink_msp432p4_sdk_3_40_01_02/source" directory to "Add dir to #include search path" window.
    - Click ARM Linker and File Search Path
      - Add "simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx/driverlib/ccs/msp432p4xx_driverlib.lib" to "Include library file..." window


<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- PROJECT LAYOUT -->
## Project Layout
```
├── main
├── testingMain
└── [Code]
     ├── [Games]
     │    ├── about
     │    ├── bestScore
     │    ├── coinFlip
     │    ├── floppyDisk
     │    ├── pong
     │    ├── rhinoRunner
     │    ├── snake
     │    └── spaceGame
     ├── [Images]      
     │    ├── aboutImages
     │    ├── backgroundImages
     |    ├── bestScoreImages
     │    ├── coinFlipImages
     │    ├── floppyDiskImages
     |    ├── menuImages
     │    ├── pongImages
     │    ├── rhinoImages
     │    ├── snakeImages
     │    └── spaceGameImages
     ├── [Menu]
     │    ├── gameHub
     │    └── menu
     └── [Utilities]
          ├── colors
          ├── init
          ├── libs
          ├── linkedList
          ├── list
          └── utilities
```

<!-- ROADMAP -->
## Roadmap

| TASK | Haroon Chaudhry | Samuel Casagrande | Francesco Poinelli |
| :---         |     :---:      |    :---:      |    :---:      | 
| Project planning | X | X | X | 
| Collect ideas |  X | X | X | 
| Project structure |  X | X | X | 
| Utilities / common functions |  X | X | X |
| Snake |  X | X | X | 
| Organizing Code Files (initial) |  X |  |  |
| Pong |   | X |  | 
| Floppy Disk |  X |  |  |
| Rhino Runner |   |  | X | 
| Space invaders |   | X |  | 
| Best score |   |  | X | 
| Images |   | X |  | 
| Menu |   | X |  |
| Menu fixing |   |  | X |
| Accelerometer issue |  X | X | X | 
| General Comments |  X | X | X | 
| Added templates / Specific comments  |  X |  |  |
| Migration to GitHub | X  |  |  |
| Tutorials |   |  | X | 
| Led |   | X |  | 
| Readme file |  X |  |  |
| Documentation.txt file |   |  | X | 
| Testing Documentation |  X |  |  |  
| Actual testing |  X | X | X | 
| Video |  X | X | X | 
| Other issues |  X | X | X | 

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- ABOUT US -->
## About us

We are a group of three students pursuing a degree in Computer Science, Communications and Electronics Engineering at the University of Trento. Our passion for technology and innovation has led us to create this project for our Embedded Software for the Internet of Things course, taught by Dr. Kasım Sinan Yıldırım.

Our goal is to provide innovative and practical solutions for the Internet of Things. We believe that the potential of the Internet of Things is immense and has the power to transform our daily lives in ways we have yet to imagine. Our project is a small step towards realizing this potential.
We are constantly striving to improve our skills and knowledge in the field of computer science, communications, and electronics engineering. Our aim is to make a positive impact in the world of technology and contribute to the growth of the Internet of Things.

If you have any questions or want to know more about our project, feel free to reach out to us through the emails listed in the next Section. 
We would be more than happy to hear from you.

<!-- CONTACT -->
## Contacts

-   Haroon Chaudhry Mohammad - [@twitter_handle](https://twitter.com/twitter_handle) - h.chaudhrymohammd@studenti.unitn.it
-   Samuel Casagrande Cecchin - [@twitter_handle](https://twitter.com/twitter_handle) - s.casagrandececchin@studenti.unitn.it
-   Francesco Poinelli - [@twitter_handle](https://twitter.com/twitter_handle) - francesco.poinelli@studenti.unitn.it


Project Link: [https://github.com/chaudhry0/Nintondo](https://github.com/chaudhry0/Nintondo)\
PowerPoint Presentation Link: [https://docs.google.com/presentation/d/1FjArqNzbcVRavWcu7ZA5t-i7vRcWXR6WLDtwkMczJLI/edit?usp=sharing](https://docs.google.com/presentation/d/1FjArqNzbcVRavWcu7ZA5t-i7vRcWXR6WLDtwkMczJLI/edit?usp=sharing)
Video Presentation Link: soon

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments
* [Embedded Software for the Internet of Things by Dr. Kasım Sinan Yıldırım](https://sinanyil81.github.io/courses/trento/2021/iot/)
* [Code Composer Studio User's Guide](https://software-dl.ti.com/ccs/esd/documents/users_guide/index.html)
* [MSP432® Peripheral Driver Library](https://schaumont.dyn.wpi.edu/ece4703b22/_downloads/7a8fc22c23fd2706dfd4d3f5256fad98/msp432-driverlib-user.pdf)
* [MSP Graphics Library](https://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/SIMPLELINK_MSP432_SDK/1.20.00.45/exports/docs/grlib/grlib-UsersGuide.pdf)
* [C Coding Standars](https://barrgroup.com/sites/default/files/barr_c_coding_standard_2018.pdf)
* [Google Drive Storage](https://www.google.com/drive/)
* [GitHub](https://github.com/)


<p align="right">(<a href="#readme-top">back to top</a>)</p>

Thank you for visiting our page! Enjoy you experience with Nintondo!

<!-- MARKDOWN LINKS & IMAGES -->
[boosterpack]: images/IMG_boosterpack.PNG
[C-logo]: https://img.shields.io/badge/C%20Language-000000?style=for-the-badge&logo=c%2B%2B&logoColor=white
[C-url]: https://en.cppreference.com/w/c/language
[CCS-logo]: images/ccstudio-transparent-final.png
[CCS-url]: https://www.ti.com/tool/CCSTUDIO
[Texas-logo]: images/Texas_Instruments_Logo.svg_32.png
[Texas-url]: https://www.ti.com/product/MSP432P401R
