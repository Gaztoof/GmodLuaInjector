# Garry's Mod Lua Executor / Scripthook

[![Build Status][travis-image]][travis-url]
[![Downloads Stats][npm-downloads]][npm-url]

This is both an executor and a scripthook for [Garry's Mod](https://store.steampowered.com/app/4000/Garrys_Mod/).

You can easily steal any server's clientside/shared lua scripts, and at the same time, execute your own.

Building in Release mode will disable the console, while building in Debug mode will also let you execute directly from the console.

Note that for now, this only works in X64

![](https://i.imgur.com/FmLXmCl.png)

## Usage

You can either inject this using your own injector, or use the included injector.
Simply put the .dll and Injector.exe in the same folder, and open Injector.exe

It should automatically inject the .DLL into the target process.


If you did this right, this is what the Injector should be saying.

![](https://i.imgur.com/vlnlGpb.png)

Press INSERT to open the menu.

## How to change architecture

You don't know whether your game is in x86, or x64?

Then it's simple, go to your Steam Library, right click on Garry's Mod, and click on Properties.

![](https://i.imgur.com/XIsyJKq.png)

After that, click on Betas, and select x86-64

![](https://i.imgur.com/KZJDXTD.png)

That's it! Your game can now run in x64.

Next time you run it, make sure you select this

![](https://i.imgur.com/OiN64SU.png)

## Contact

You can contact me on [Telegram](https://t.me/Gaztoof), at t.me/@Gaztoof

[This](https://www.youtube.com/channel/UCB7rQNzTsaoS2-I0Z4byUxA) is my YouTube channel.

## Contributing

1. Fork the project (<https://github.com/Gaztoof/GmodLuaInjector>)
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request


<!-- Markdown link & img dfn's -->
[npm-url]: https://npmjs.org/package/datadog-metrics
[npm-downloads]: https://img.shields.io/npm/dm/datadog-metrics.svg?style=flat-square
[travis-image]: https://img.shields.io/travis/dbader/node-datadog-metrics/master.svg?style=flat-square
[travis-url]: https://travis-ci.org/dbader/node-datadog-metrics
[wiki]: https://github.com/yourname/yourproject/wiki
