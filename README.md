<img src=https://chuck.cs.princeton.edu/doc/images/chuck-logo2023w.png alt="logo" width=128 height=128 />

<h1>Spherical Harmonics in ChucK</h1>
<p>This ChucK chugin is designed as a class library that provides simple methods of calculating cartesian coordinate systems using spherical harmonics. You can easily call coordinates from this library in up to 3rd order spherical harmonics. Simply use functions such as ".x(direction angle, elevation angle)" to call your x coordinate. All coordinate functions receive the arguments, directional angle and elevation angle. The W coordinate value is 1 according to SN3D standards. You can also call the .all function that, given direction, elevation, a chuck float array of the necessary size, and order, will calculate your complete coordinate system according to the order provided. Please ensure that the float array is of the correct size, as an array with 18 entries will not allow calculation of 16 coordinates.</p>

<h4> <span> · </span> <a href="https://github.com/SaintEverett/AmbiMath.chug/blob/master/README.md"> Documentation </a> <span> · </span> <a href="https://github.com/SaintEverett/AmbiMath.chug/issues"> Report Bug </a> <span> · </span> <a href="https://github.com/SaintEverett/AmbiMath.chug/issues"> Request Feature </a> </h4>


</div>

## About the Project

### Features
- Up to 5th order SN3D ambisonic coordinate systems.
- Individual or all coordinates calculable at any time.


## Getting Started

### Prerequisites

- Install ChucK on your computer <a href="https://chuck.stanford.edu/">here</a>


## FAQ

- How do I install this chugin?
  - Simply drop the .chug file in your "chugins" folder within your ChucK build.

- I don't have a "chugins" folder in my ChucK build, what do I do?
  - If you have not yet built your chugins library (should come with ChucK install as of 1.5.x.x), then you can find information on the build here... https://github.com/ccrma/chugins


## License

Distributed under the MIT License. See LICENSE.txt for more information.

## Contact

Everett Carpenter - - carpee2 [at] rpi [dot] edu

Project Link: [https://github.com/SaintEverett/AmbiMath.chug](https://github.com/SaintEverett/AmbiMath.chug)
