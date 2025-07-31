# 🎲 Yahtzee Game in C

This project is a terminal-based implementation of the classic dice game **Yahtzee**, written in the C programming language. It allows a human player to compete against a computer opponent, with both taking turns to roll dice, choose categories, and accumulate points.

---

## 📌 Features

- Human vs. Computer gameplay
- Implements all 13 standard Yahtzee scoring categories:
  - Ones to Sixes
  - Three of a Kind
  - Four of a Kind
  - Full House
  - Small Straight
  - Large Straight
  - Yahtzee
  - Chance
- Three rolls per turn allowed (with rerolling option)
- Tracks used categories for each player
- Upper section bonus of +35 points when scoring ≥63 in Ones–Sixes
- Simple AI decision-making for the computer
- Clean and interactive terminal interface

---

## 🛠️ Requirements

- C compiler (e.g. `gcc`, `clang`)
- Terminal / command prompt

---

## 🚀 How to Compile and Run

### 💻 Compilation

```bash
gcc yahtzee.c -o yahtzee
