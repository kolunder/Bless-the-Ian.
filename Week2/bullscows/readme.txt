BULLS AND COWS.

Rules: 
This is the game for 2 PLAYERS. FIRST PLAYER chooses a secret 4-DIGIT CODE.\nSECOND PLAYER - makes attempts to guess the code.
They can offer ANY COMBINATION of 4 digits (WITHOUT REPETITIONS) - for each attempt the program answers with a HINT
THE HINT consists of TWO VALUES:
- FIRST tells how many digits are GUESSED CORRECTLY AND ARE IN CORRECT POSITIONS
- SECOND tells how many digits are GUESSED CORRECTLY BUT ARE IN WRONG POSITIONS.
FOR EXAMPLE, if the SECRET VALUE is 1492 and SECOND`S GUESS is 2013 - THE HINT IS 0-2.
And if the GUESS is 1865 - then the HINT would be 1-0.

Progress: 
The development has so far taken surprisingly long time.
I appear to be stuck on the validation function. Writing it out with printf statements
seems to be doing something to the memory and makes the function work as intended. However,
once printf is removed, the whole thing goes nuts. However, I do have a few ideas on how to solve it and the rest of the program,
like user input, comparison of the two guesses and the output of the hint appear to be trivial, as the validation 
and conversion functions are already in place.

15/10/17
Fixed the issues of the previous week. Game works almost as intended, except Validation Checks do not work on user guesses. That is the last stage, as all other features work as intended. Please advise me on how to correct that last issue. Thank you!