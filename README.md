# The Database Project

> I know I'm bad at names no need to mention it

## **If you're reading this it means that you're in the Development Branch**

## **Do note this is only a mvp, and not meant for implementation**

### What is this project

I would describe this project as a random idea that came to while learning about working with files in C, you can probably tell as much just by looking at the code.

### If not for implementation than for what

This project is mostly meant to learn the inner workings of relational databases like MySQL, MariaDB, etc. For the most part I only really made it on the whim and don't think of changing much to make it able to be implemented in any system.

### What does the future look like for this project

At the moment I am for all intensive purposes unsure, I will keep developing it until I feel satisfied with it but from then on I will probably leave it be in case I ever want to keep working on it again or work off it in the distant future.

### Important stuff to now to run properly

If you wish to run this,(Honestly don't know why you would), you should know some important details, currently there are 2 branches of the repo, **Main** and **Development**, besides the names whats the difference:

1. **Stability**:
Currently Main is the only stable build I have, while development is currently incredibly unstable and is probable to change in its life time.

2. **Features**:
The current features in Main are simplistic and are the first to be developed meaning they're out of date. Mean while development has some of the most recent features, with the downside that it can change at any moment as said before.

Knowing that in case you choose to try one out what should you keep in mind. In the first place the main branch only allows the use of a file called **"basicdatabase.txt"** as its storage, and it mus have the following text in the first line:

> Key, User, Password.

As this declares the fields to be used and are the only fields allowed to be used in the file.

In the case of the Dev Branch you can freely use any file as the storage, if the file is not found in the system it will be created and the same fields will be inserted into it. Now the only down side is that the fields aren't changeable.

### Planned Features for the near future

Some of these are just ideas and I'm unsure if they are currently possible with my abilities but I'll figure it out as I go:

- Custom fields
- Database, tables and relations
- Custom field searching
- Better CLI looks

### Changelogs

- [`60f2587`](https://github.com/EfrenDaMo/DatabaseProyect/commit/60f2587b0c327275453a27d4aa31521f46be6a09) Created repo, programmed in a basic database, finished up the project

- [`9274cee`](https://github.com/EfrenDaMo/DatabaseProyect/commit/9274ceec72b11ca8b42180086ad14aafd6e1c7b5) Made minor changes toward commentating the code

- [`f33e082`](https://github.com/EfrenDaMo/DatabaseProyect/commit/f33e082e987a0b235268d41b03a74a76ef7ae8ac) Made it possible to open databases by now, added comments to functions, other minor changes

- [`b6452a3`](https://github.com/EfrenDaMo/DatabaseProyect/commit/b6452a37e8fda66f6498da95e7c9f41465aaf654) Cleaned up minor issues, and cleaned up memory management

- [`fe1d018`](https://github.com/EfrenDaMo/DatabaseProyect/commit/fe1d0186ab3f42d3e837f60e6cc877a9454b56d1) Cleaned up code, made variables easier to understand, optimized some other of possible memory issues

- [`3aa5cdf`](https://github.com/EfrenDaMo/DatabaseProyect/commit/3aa5cdf3ef44478f88c94dcf6576d81fba16f36e) Created README.md for the Dev Branch

- [`05542fe`](https://github.com/EfrenDaMo/DatabaseProyect/commit/05542fe19742b971e582a44a3110cb1ee9812d82) Added changelog to the ReadMe

- [`e99e775`](https://github.com/EfrenDaMo/DatabaseProyect/commit/e99e775d002bcd4daf0cfead9a47a9e9b9b611a0) Made changes to fix mistake is changelog in ReadMe

- [`a2f4934`](https://github.com/EfrenDaMo/DatabaseProyect/commit/a2f493484de71248aa4265388a2bff847818b092) Added screen clearing every time a new operation is done

- [`a83508d`](https://github.com/EfrenDaMo/DatabaseProyect/commit/a83508dfeeacaf1d3a7643c13ab71b2bed3c178f) Change line reading from file to prevent stack overflow

- [`90c8501`](https://github.com/EfrenDaMo/DatabaseProyect/commit/90c8501e5e04315a42974a367dbe4f88a1dc6795) Fixed seg fault near the beginning of system, fixed screen clearing to work on most systems

- [`69d0638`](https://github.com/EfrenDaMo/DatabaseProyect/commit/69d063820249ec7f932e84abcfa46011a46e4f0f) Refactored to improve file handling and user prompts, added platform-specific includes for Windows and Linux.

- [`c198fa2`](https://github.com/EfrenDaMo/DatabaseProyect/commit/c198fa285fb8eb563dfc334b326e225c370b6268) Implemented the return to all the previous menus

- [`d98ccf7`](https://github.com/EfrenDaMo/DatabaseProyect/commit/d98ccf716b7089b499f4bc5c5e974cf503adba61)  Makes it so the that the system keeps looping till user quits, moved input reading to functions to make it easier

- `Current` Added timer to all lookup functions, to measure lookup time; Updated .gitignore

### Thanks && other stuff

If you have any recommendations or ideas that should be implemented for the project, feel free to tell me.

Thanks to the crazy chick who listens to me rant on and on about this project in the middle of class when I should be paying attention to the professor.
