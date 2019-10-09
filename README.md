# Data-Structure-Game-Impossible-AI-Hangman-
## Data Structure Game "Impossible AI Hangman" USING C Programming. 

Wheel of Misfortune is a two­player word game that goes like this. Player 1 picks a secret word, and tells player 2 the length. (For example, ­­­­­ would mean that the word selected by player 1 has five letters.) Player 2 then begins guessing letters. For each letter guessed by player 2 that appears in the word, player 1 reveals the positions of that letter. Otherwise, if the letter does not occur at all in the word, player 2 loses a guess. Player 2 wins the game if they are able to fully uncover the word before exhausting their allowed number of guesses. Player 1 wins if player 2 runs out of guesses.

I will be implementing Wheel of Misfortune game where the computer has the role of player 1, and a human has the role of player 2. However, rather than choosing a word at the beginning of the game like a good little computer is supposed to do, this nasty computer opponent is going to cheat and make it very difficult for the human to win. It will actively dodge human efforts to determine the word, as I'll explain now. 

When the game starts, you will tell the computer the length of the word you want to guess. Let's say that you choose a word­length of four letters, so that you see ­­­­ as the current representation of the word. Rather than playing fair and committing to one particular four­letter word from the outset, the computer instead compiles a list of every four­letter word in its dictionary. For simplicity, let's assume that it has exactly the following four­letter words: ally beta cool deal else flew good hope ibex. For your first guess, let's say you choose the letter e. The computer now must tell you whether there are any e's in the word and, if there is at least one e, it must also show you the word with each e written in its proper position.

But how can the computer do this, since it has not chosen a word yet? The trick is for the computer to divide all current words into word families based on where the e's lie in each word. Here is our vocabulary again, with the e's in bold: ally beta cool deal else flew good hope ibex. There are five word families:
­­­­, which contains the words ally, cool, and good ­e­­, containing beta and deal
­­e­, containing flew and ibex
e­­e, containing else
­­­e, containing hope

What the computer will do is choose one of these word families, then uncover the e's that occur in each word of that chosen family. There are several means by which the computer could choose a family; in this assignment, the computer will always choose the family with the most words. If there is a tie for the most words, the computer will chose any one of the families tied for the most words.

As evidenced in our running example, the largest word family is of size three (the family ­­­­). The computer will choose this word family, reduce its candidate word list (now ally, cool, and good), and report to you that there are no e's in the word. Nasty!

It's not necessarily the case that the chosen word family includes no copies of your guess. (Remember, the computer is using the heuristic of always choosing the largest family. This is not always optimal.) To demonstrate this, let's say that the computer is working with ally, cool, and good, and your next guess is o. This time, there are two word families:
­oo­, containing cool and good ­­­­, containing ally.

The computer would choose the first word family, reducing its word list to cool and good, and revealing two o's in the word.
Note that if you guess a letter that does not appear anywhere in the computer's current word list, or your letter appears in the same position of every single word in the current word list, the computer will "divide" the word list into a single family consisting of all words. This really isn't a special case at all if your code is sufficiently general (as it should be).

There are two ways that the game can end. The first is that you are lucky enough to pare the computer's word list down to a single word, in which case you win the game. The second (much more common :) ) case is that you exhaust all of your guesses without guessing the computer's word. In this latter case, the computer can just pick any word at random from its current list, and report this word to you. All words in the current list are indistinguishable to you, since they are all in the same word family.

