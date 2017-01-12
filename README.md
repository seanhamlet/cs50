# CS50x

My solutions for [CS50x - Introduction to Computer Science](https://www.edx.org/course/introduction-computer-science-harvardx-cs50x), an online course by Harvard University.

## Week 0

+ Develop game with Scratch. Play my finished game [here](https://scratch.mit.edu/projects/113792557/)
+ Requirements:
  + Use two sprites.
  + Have at least three scripts total.
  + Use at least one condition, one loop, and one variable.
  + Use at least one sound.

## Week 1 - pset1

1. hello.c  - Prints "Hello, world" to the terminal. Usage: ./hello
2. water.c  - Converts time in shower (minutes) to water used (bottles). Input: minutes in shower. Usage: ./water
3. mario.c  - Prints pyramid from Mario using hashes. Input: height. Usage: ./mario
4. greedy.c - Converts change in dollars number of coins due. Coin values: quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢). Rule: Use the least number of coins. Usage: ./greedy

## Week 2 - pset2

1. initials.c - Prints capitalized initals of full name. Input: full name (capitalized or not). Usage: ./initials
2. caesar.c   - Encrypts plain text using Caesar cipher algorithm. Inputs: secret key, plain text. Usage: ./caesar <secretkey>
3. vigenere.c - Encrypts plain text using Vigenere cipher algorithm. Inputs: secret key, plain text. Usage: ./vigenere <secretkey>

## Week 3 - pset3

1. find
Requirements:
  + Write a sorting algorithm - chose selection sort
  + Write a search algorithm  - chose binary search (requires sorted array)
  + Use generate.c to generate a list (user chooses size) of pseudorandom numbers with an optional seed point input. Use find.c to determine if a number is within list of numbers. Binary Search with Selection Sort was used as the search/sort algorithm for find.c and are functions in helpers.c.
Usage: ./generate 1000 50 | ./find 127

2. fifteen - Play game of fifteen. Usage: ./fifteen <boardsize>

## Week 4 - pset4

1. whodunit.c - Umasks red-filtered bmp image to reveal whodunit! 
Usage: ./whodunit infile outfile
  + Example: ./whodunit clue.bmp verdict.bmp
  
2. resize.c - Resized bmp image
Usage: ./resize <resize-factor> infile outfile

3. recover.c - Recovers JPEGs from a forensic image (card.raw)
Usage: ./recover

### Week 5 - pset5

1. speller.c - Implements a spell checker
Usage: speller [dictionary] text

### Week 8 - pset6

