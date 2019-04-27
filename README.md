# Type driven Development mit C++
Vortrag für [ADC++2019](http://www.adcpp.de/2019/) (22.-23. Mai 2019 in Regensburg)

## Slide Tech

* [AsciiDoctor](https://github.com/asciidoctor/asciidoctor) as hackable html slide generator with a lot of features
* [Bespoke.js](https://github.com/bespokejs/bespoke) as a flexible html slide framework
* [Patched AsciiDoctor-Bespoke](https://github.com/arBmind/asciidoctor-bespoke/tree/patch-1) that allows the nested code display
* [Patched Bespoke-Bullets](https://github.com/arBmind/bespoke-bullets) to allow better interactions through API
* [Patched Bespoke-Hash](https://github.com/arBmind/bespoke-hash) that uses the extended bullets API
* [Patched Bespoke-OnStage](https://github.com/arBmind/bespoke-onstage) with some customizations and fixes for my setup
* [Gulp](https://github.com/gulpjs/gulp) to automate regeneration and push slide updates to the browser

## Code Tech

The `code/` folder contains a compilable version of all the code examples from the slides.

You need a C++17 capable compiler. QBS is used as project management, but it should be easy to setup with any build system.

*Warning:* All the code is for learning and demonstration purposes only and has no production quality.
Especially the slide code is aimed to fit on slides and lacks a lot of best practices.

## License

The slides here are available under the terms of the Creative Commons Attribution-ShareAlike license.
[(cc-by-sa-license)](https://creativecommons.org/licenses/by-sa/2.0/)

Photos

* [Explosion](https://www.flickr.com/photos/purpleseadonkey/4775066884) [(cc-by-license)](https://creativecommons.org/licenses/by/2.0/)
* [Grand Valley cattle drive](https://www.flickr.com/photos/stormfarm/14704893215) [(cc-by-sa-license)](https://creativecommons.org/licenses/by-sa/2.0/) - Cropped & Auto Toning
