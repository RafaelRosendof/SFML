### Para rodar 

---

### Comandos

```bash
sudo pacman -Syu
sudo pacman -S install SFML
```
Para debian
```bash
sudo apt update
sudp apt install SFML
```

```bash
clang++ sfml.cpp Hero.cpp Enemy.cpp Rocket.cpp -o sfml -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

./sfml

```

### Caso use o g++ ao invés do Clang

```bash
g++ sfml.cpp Hero.cpp Enemy.cpp Rocket.cpp -o sfml -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

./sfml
```

