# Feedback Gruppe24 - Tetris

Programmet krasjer (som du sikkert er klar over) på:

```cpp
 bool boardHasBrick = m_board[totalX + nextY * m_width];
```
her hadde det vært en ide å lage en variabel for indeksen:

```cpp
size_t index =  totalX + nextY * m_width;
bool boardHasBrick = m_board[index];
```
Da er det lettere å debugge koden (og øker generell lesbarhet).

```cpp
inline auto createBox
```
Du har oppdaget att frie funksjoner implementert i header må markeres `inline`. Bra.
PS. Ville ikke brukt namespace `threpp` på den. Det ville bety at funksjonen er en del av threepp bibliotket, 
noe den ikke er.

I klassen `Board` har du `protected` 4(!) ganger og `public` 2 ganger.
Kan du ommrokkere koden så du står igjen med en av hver?

Ønsker å se bruk av `add_library` som du da linker inn i din `add_executable` (og testene du etterhvert skal legge inn).

På tide å endre navnet på vinduet til noe annet enn `"threepp demo"`. Samme med navnet på prosjetket og din executable target.

```cpp
Board::Board()
    :
    m_board({ 0 })
{
```
Er koden over visuelt behagelig?

`if (brick.get())` -> Bare `if (brick)`.

Mye som mangler rent teknisk enda så vanklig å kommentere så mye. 
Se til at du kommer i mål til grei tid i forhold til det du planlegger.

Koden hadde gjort seg med flere overordende kommentarer på hva som skjer. 
La merke til at programmet oppfører seg annerledes om man trykker på noen taster, men endringen kommer ikke frem visuelt sett, 
så det er en mismatch mellom visuelisering og den underliggende logikken.

---
Tilbakemeldingen kan inneholde feil og mangler. Ta kontak ved spørsmål.
