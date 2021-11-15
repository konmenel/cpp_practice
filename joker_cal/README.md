# Introduction
This is a tool I created as practice for C++ and to prove that lottery is a waste of money, especially to my mother.

"Joker" is the name of the national lottery in Greece and Cyprus. `joker_cal` is a command line calculated applicationthat calculates how many draws will it take for you to reach a target percentage (i.e. 50%). This target percentage is the probability for you to win at least once. Addictionally, if you provide a jackpot and an estimation of the number of tickets being sold the expected value of the ticket will be calculated.

# Dependencies
No dependancies, just download the binary and run it or the files from source.

# To run
To run the application open a terminal on the directory of the binaries and type:
```
>>./joker_cal <target-probability> <jackpot> <total-number-of-tickets> <options>
```
`<target-probability>` is the percentage in decimal format (i.e. 0.5 for 50%)
`<jackpot>` Optional. The value of the jackpot in euros.
`<otal-number-of-tickets>` Optional. The estimate of the amount of ticket being sold.
`<options>` Currently not implemented. `-o` to desplay results of calculation on screen.

# How "Joker" works
To win joker you have to correctly guess 5 number from the first field and 1 from the second field. The first field contains 45 number and the second 20.

# How the tool works
## Probability for at least 1 win.
to be filled...
## Expected value per ticket
to be filled...


# References
- Joker Guide: https://www.opap.gr/en/how-to-play-joker
