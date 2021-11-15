# Introduction
This is a tool I created as practice for C++ and to prove that lottery is a waste of money, especially to my mother.

"Joker" is the name of the national lottery in Greece and Cyprus. `joker_cal` is a command line calculated applicationthat calculates how many draws will it take for you to reach a target percentage (i.e. 50%). This target percentage is the probability for you to win at least once. Addictionally, if you provide a jackpot and an estimation of the number of tickets being sold the expected value of the ticket will be calculated.

# Dependencies
No dependancies, just download the binary and run it or the files from source.

# To run
To run the application open a terminal on the directory of the binaries and type:
```
> ./joker_cal <target-probability> <jackpot> <total-number-of-tickets> <options>
```
`<target-probability>` is the percentage in decimal format (i.e. 0.5 for 50%)
`<jackpot>` Optional. The value of the jackpot in euros.
`<total-number-of-tickets>` Optional. The estimate of the amount of ticket being sold.
`<options>` Currently not implemented. `-o` to display results results during the calculation process.

Alternatively, you can just run the binary (.exe) without any arguments and fill the answers in the program.

# Details on Joker
## How to play
To win the Jackpot in Joker you have to correctly guess 5 number from the first field and 1 from the second field. The first field contains 45 number and the second 20. You can select more than 5 number from the first field and more than 1 number in the second field, although you have to pay extra for each number. An online tool on the official website exist for calculating the cost. For simplicity we will not consider any of those cases. The standard fee for a ticket for 5+1 numbers is 0.5€.

## Prize tiers
Joker offers 8 prize tiers are available depending on how many correct guesses you made. All the tiers all listed below.
![Prize tiers](https://www.opap.gr/documents/63996/65648/deltio1EN.png/543afca2-ccfb-c6ed-1e58-07cebe74dc24?t=1508750210462&version=1.0)

# How the tool works
## Probability for at least 1 win.
to be filled...
## Expected value per ticket
to be filled...


# References
- Joker Guide: https://www.opap.gr/en/how-to-play-joker
