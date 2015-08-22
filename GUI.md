Gui Spielfeld


# Details #

Gui Spielfeld
Aufteilung
BaghChal:QMainWindow
> centralWidget:QWidget
> > unusedGoatsField:QWidget
> > > title\_00:QLabel (“Ziegen”)
> > > unusedGoat\_xx:QWidgets (20x)
> > > > goat\_xx:AvatarWidget (20x)(abgeleitet von QWidget)
> > > > > goatImage:QLabel

> > playingField:QWidget
> > > box\_00:BoxWidget (abgeleitet von QWidget)
> > > > tiger\_00:AvatarWidget (abgeleitet von QWidget)

> > > box\_01:BoxWidget abgeleitet von QWidget
> > > box\_02:BoxWidget abgeleitet von QWidget
> > > box\_03:BoxWidget abgeleitet von QWidget
> > > box\_04:BoxWidget abgeleitet von QWidget
> > > > tiger\_01:AvatarWidget abgeleitet von QWidget

> > > box\_10:BoxWidget abgeleitet von QWidget
> > > …

> > rippedGoatsField:QWidget
> > > title\_01 QLabel  “Gefressene Ziegen”

> > 5x rippedGoat\_xx QWidget
menuBar  QMenuBar

> menuGame  QMenu
> actionNewGame  QAction
> spacer	QAction
> actionLoadGame  QAction
> actionSaveGame  QAction
> spacer  QAction
> actionQuitGame  QAction
> menuHelp  QMenu
> > actionHelp  QAction
> > > actionInfo  QAction
statusBar  QStatusBar


Add your content here.  Format your content with:
  * Text in **bold** or _italic_
  * Headings, paragraphs, and lists
  * Automatic links to other wiki pages