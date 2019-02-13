# Dynamic Programming Assignment

#### Fall 2018

Compile using command: `g++ -g -Wall -std=c++11 grid.cpp -o grid`

Run using command: `./grid`

### Original assignment description:

#### Background

You are Brian! You have spent the entire night painting "ROMANES EUNT DOMUS" all over Jerusalem. There is just one spot left. Unfortunately, it's far away, and your grammar iswrong, so if any of the guards catch you, they will correct you on the proper use of the vocative plural declension and imperative conjugation. This will exhaust poor Brian, who has been up all night.

Fortunately, Brian has the support of the Judean People's Front (or was it the People's Front of Judea?), who can encourage Brian and remove some of his exhaustion by inviting Brian to their conference on "Other than sanitization, medicine, education, and order, what have the Romans ever done for us?".

#### Description

Brian is at the top left of an N x N grid, and needs to get to the bottom right in order to paint his message. To reach his destination as soon as possible, he'll only move along the shortest way, i.e. moving rightward and downward. Along the way, Brian can encounter Roman guards marked as negative integers, where the magnitude is the amount of damage they deal. The positive integers are tiles that heal Brian that amount of HP, P are tiles that prevent Brian's next damage, and D are tiles that double Brian's next healing effect. If Brian reaches 0 HP or less, he collapses and the mission fails, so prevent that!

No matter how many P tiles and D tiles Brian encounters, their effects don't stack. For example, if Brian walks on a D tile when he's already in the state of "doubling next healing effect", nothing happens. When Brian next encounters a healing tile, the healing will be doubled. Afterwards, Brian returns to a \normal" state. The same applies for P tiles.

What is the minimum amount of life Brian needs in order to complete his task?

#### Input Format

Read from standard input. The input is guaranteed to be well-formed, as described below:

The first line contains an integer N. Next N lines describe the grid, each containing N strings
separated by space. For each string:

- If the string is P, it indicates tiles that prevent Brian's next damage.
- If the string is D, it indicates tiles that double Brian's next healing effect.
- Otherwise, the string should actually be a non-zero integer x.
  1. x > 0: the tile will heal Brian x HP.
  2. x < 0: guard on the tile will deal jxj damage to Brian.
