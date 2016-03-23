Overload
===================

Overload is a loading overlay for the game League of Legends, aimed to replace current game loader with a more useful one.
It has enhanced informations as well as more appealing graphics, animated art and user interactions, things that the current loader lacks.

What is it doing?
-------------
Overload start a daemon looking for the starting of league of legends process on your computer. Once the game is launched, it will quickly create a window with a new loader on the top of the  game and will close it once the loading is finished and the game start. This mechanism is called an overlay, and is commonly used to enhance a game experience.

**League of legends Loading screen:**
![Old loader](http://s14.postimg.org/db3vo7h81/old_Loader.png "Old loader")
- static art
- nearly zero information
- no interaction

**Overload:**
![Overload](http://s12.postimg.org/azstjegtp/new_Loader.png "Overload")
- users information on their champions, current season rank, statistics of the player
- runes currently in use by players
- animated art and animated transitions
- mouse-over interaction to retrieve specific player information

How does it do it?
-------------
As stated above, it's an overlay window, we just create our new loader on the top of the old one.

![Overlay](http://s9.postimg.org/rrw8nj4xr/overlay.png "Overlay")

Current user information is retrieved in local league of legends files.
Other players information are retrieved thanks to League of Legends API, that allows us to asks informations about people playing with any user.


![not mul](http://s11.postimg.org/6j7eatjpv/servers.png "not uml")

*Warning: not uml approved*

We need an intermediate server because you can't really ask Riot for user informations without a developper key. This key allows you up to 10 request every 10 seconds, or 500 every 10 minutes. Enough for this little project, but we can't afford to let people use this key for other projects, so our server makes the request to Riot and send the informations to the client.

Building it
-------------
Overload (client side) is using some libraries you will need to install before anything:
[SFML 2.3](http://www.sfml-dev.org/download-fr.php)
[Cef 3 (branch 2454)](https://cefbuilds.com/)
[CppRest](https://casablanca.codeplex.com/wikipage?title=Http%20Client%20Tutorial)

Overload (server side) has no git repository yet, but will have it's own readme.

Once every of those libraries are correctly linked, it should build. Probably. This readme is not complete, as is this project. 

What is missing
-------------

A lot.
We have no idea how to retrieve user loading bar (the percentage). Riot don't send this information.
We tried OCR (implementing a freeman algorithm, since TesseractOCR was really not convincing) and it works fine, but will need a lot of change to works with every configuration (screen resolution). You won't find any OCR in this repo, though.