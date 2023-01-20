<br />
<div align="center">
  <a href="https://github.com/github_username/repo_name">
    <img src="images/logoNintondo.png" alt="Logo" width="140" height="80">
  </a>

<h3 align="center">Nintondo</h3>

  <p align="center">
    powered by Unitn students
    <br />
    <a href="https://github.com/chaudhry0/Nintondo/tree/master/Documentazione"><strong>Explore the documents »</strong></a>
    <br />
    <br />
    <a href="https://github.com/github_username/repo_name">View video Demo</a>
    ·
    <a href="https://github.com/github_username/repo_name/issues">Report Bug</a>
    ·
    <a href="https://github.com/github_username/repo_name/issues">Request Feature</a>
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
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

[![Boosterpack image][boosterpack]](https://www.ti.com/tool/BOOSTXL-EDUMKII)

About The Project Text
About The Project Text
About The Project Text
About The Project Text
Do a search and replace with your text editor for the following: `github_username`, `repo_name`, `twitter_handle`, `linkedin_username`, `email_client`, `email`, `project_title`, `project_description`

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Built With
* [![C][C-lan]][C-url]
* [![CCS][CCS-ide]][CCS-url]
<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

Welcome to Nintondo repository! In order to get started and have a working local copy of Nintondo follow these simple example steps.

### Prerequisites

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

<!-- USAGE EXAMPLES -->
## Usage
examples of how a project can be used. Additional screenshots, code examples and demos

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ROADMAP -->
## Roadmap
- [ ] Feature 1
- [ ] Feature 2
- [ ] Feature 3
    - [ ] Nested Feature
 
 <p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

-   Haroon Chaudhry Mohammad - [@twitter_handle](https://twitter.com/twitter_handle) - h.chaudhrymohammd@studenti.unitn.it
-   Samuel Casagrande Cecchin - [@twitter_handle](https://twitter.com/twitter_handle) - francesco.poinelli@studenti.unitn.it
-   Francesco Poinelli - [@twitter_handle](https://twitter.com/twitter_handle) - s.casagrandececchin@studenti.unitn.it


Project Link: [https://github.com/chaudhry0/Nintondo](https://github.com/chaudhry0/Nintondo)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* []()
* []()
* []()

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
[boosterpack]: images/IMG_boosterpack.PNG
[C-lan]: https://img.shields.io/badge/C%20Language-000000?style=for-the-badge&logo=c%2B%2B&logoColor=white
[C-url]: https://en.cppreference.com/w/c/language
[CCS-ide]: images/ccstudio.jpg 
[CCS-url]: https://www.ti.com/tool/CCSTUDIO
