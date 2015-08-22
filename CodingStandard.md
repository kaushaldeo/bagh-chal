# Coding Standards und Doxygen Formatierung #

Andere Vorschläge sind willkommen. Ich bin für folgende:

## Coding Standard ##

  * Kommentare in englisch
  * Nach Schleifen, Abfragen, Methodendefinition Klammer auf nächste Zeile, bsp:
```
if (true)
{
    return;
}
```


  * Einrücken immer **4 Leerzeichen, keine Tabs verwenden,** ggf. Editor anpassen
  * Alle Variablen in englisch, CamelCase:
```
int thisIsMyVariable = 1;
```
  * Defines auslagern


## Doxygen Formatierung ##

siehe:
http://www.stack.nl/~dimitri/doxygen/docblocks.html#specialblock

Für jede Klasse/Methode die einigermassen steht, bitte gleich Doxygen Infos hinzufügen.

Ich bin hier für den **JavaDocStyle** mit @.

```
/**
* A pure virtual member.
* @see testMe()
* @param c1 the first argument.
* @param c2 the second argument.
*/
`virtual void testMeToo(char c1,char c2) = 0;`
```

Wir können aber auch den C-style nehmen mit !.

Wenn wir diese immer schön nachführen, reicht nämlich am Ende nur noch ein "doxygen `<config-file>`" für das Tech-Manual.


## SVN Commits ##

Jeder Commit mit einem Kommentar versehen.


---


Viel Spass beim Coden!