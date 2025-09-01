#define __STDC_WANT_LIB_EXT1__
#include <iostream>
//#include <Windows.h>
#include <cstdlib>
#include <ctime>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stuffs {
	int cardsused = 0;
	int dealertotal = 0;
	int total = 0;
	bool onecards = false;
	bool twocards = false;
	bool sixcards = false;
	bool acepickedplayer = false;//ace pulled by player, changes probabilities
	bool playerforme1 = false;//program is playing instead of player if true
	char cards[312][3] = { "as", "ad", "ac", "ah", "ks", "kd", "kc", "kh", "qs", "qd", "qc", "qh", "js", "jd", "jc", "jh", "1s", "1d", "1c", "1h", "2s", "2d", "2c", "2h", "3s", "3d", "3c", "3h", "4s", "4d", "4c", "4h", "5s", "5d", "5c", "5h", "6s", "6d", "6c", "6h", "7s", "7d", "7c", "7h", "8s", "8d", "8c", "8h", "9s", "9d", "9c", "9h" };//array for deck of cards, first char is the rank, and the second char is the suite (no joker)
	char holecard[40] = "";//string for the holecard
};

struct card {
	int valuecard;
	char CardNamre[40] = "";
};


void shuffle(stuffs &yo, struct card (&cardarray)[312])//to shuffle the deck
{
	srand((unsigned int)time(NULL));//sets seed to time 0 ??
	char tmp[1][3] = { "" };//temp string array for shuffling
	int r, i;
	int x = 52;
	char tempp[40][40];
	int temp = 0;
	std::cout << "shuffling";
	if (yo.onecards == true) {
		x = 52;
	}
	else {
		if (yo.twocards == true) {
			x = 104;
		}
		else {
			if (yo.sixcards == true) {
				x = 312;
			}
		}
	}
	for (int rrr = 0; rrr < 20; rrr++)//shuffles the deck 20 times
	{
		//Sleep(100);//sleep for 0.05 seconds to change seed
		for (i = 0; i < x; i++)//for all the deck
		{
			r = rand() % (x);//random number between 0 and 51
			strcpy(tmp[0], yo.cards[i]);//1st store in array tmp is now the string in the i store of ranks array
			strcpy(yo.cards[i], yo.cards[r]);//changes ranks i to a random string in array ranks
			strcpy(yo.cards[r],tmp[0]);//swaps place r in ranks with place i in ranks

			temp = cardarray[i].valuecard;
			cardarray[i].valuecard = cardarray[r].valuecard;
			temp = cardarray[i].valuecard;

			strcpy(tempp[0], cardarray[i].CardNamre);
			strcpy(cardarray[i].CardNamre, cardarray[r].CardNamre);
			strcpy(cardarray[r].CardNamre, tempp[0]);
		}
		//for (i = 0; i < 52; i++) {// TO SEE HOW RANDOM THE SHUFFLES ARE/ IF THEY ARE WORKING PROPERLY
		//	std::cout << i << yo.cards[i] << " ";
		//}
		//std::cout << " end" << std::endl;
	}
	std::cout << " (complete)" << "\n" << std::endl;//when shuffling complete this is shown
}

int random_card(bool dealer, bool donotshow, stuffs &yo, struct card(&cardarray)[312])//generate a random card, returns cards value, parameter dealer to say whether it is the dealer generating a card, donotshow to say whether the card should be shown
{
	int randcard = 0;//card value
	int i;

	if (yo.cardsused == 52) {//if all of deck has been used
		shuffle(yo, cardarray);//shuffle deck
		yo.cardsused = 0;//set cardsuesd to 0 this if statement can be called again in 52 cards
	}

	char randomcard[] = "yo";//initialising random card string from deck
	
	strcpy(randomcard, yo.cards[yo.cardsused]);//copy the string from cards array to random card string

	char secondpart[40] = "";//string for card name

	if (cardarray[yo.cardsused].valuecard == 11) {
		if (dealer == true && yo.dealertotal <= 10) {//if it is the dealer generating a card and the dealer's value is less than or equal to 10
			randcard = 11;//dealer will have ace value of 11
		}
		else {
			if (dealer == true && yo.dealertotal > 10) {//if the dealer's value is greater than 10 then the value must be 1 or the dealer would instantly lose
				randcard = 1;
			}
		}
		if (dealer == true) {
			yo.dealertotal = cardarray[yo.cardsused].valuecard;
			std::cout << cardarray[yo.cardsused].CardNamre;
		}
		if (dealer == false) {//player generating a card
			yo.acepickedplayer = true;
			if (yo.playerforme1 == true) {//program playing
				if (yo.total <= 10) {//same as dealer logic
					randcard = 11;
				}
				else {
					if (yo.total > 10) {
						randcard = 1;
					}
				}
			}
			else {// player is playing
				std::cout << "11 or 1: " << std::endl;//choice for 11 or 1 value
				while (!(std::cin >> i) || (i != 11 && i != 1)) {
					std::cin.clear();
					std::cin.ignore(1000, '\n');
					std::cout << "11 or 1: " << std::endl;
				}
				if (i == 11) {//player inputs 11
					randcard = 11;// then card value is 11
				}
				else {
					randcard = 1;// if not 11 then must be 1
				}
			}
			yo.total = cardarray[yo.cardsused].valuecard;
		}
	}
	
	yo.cardsused++;//card will be used so incrementing cardsused value

	switch (randomcard[0]) {//the first character of randomcard string, for card ranks
	case 'j':
		strcat(secondpart, "Jack");//put the rank string into the string for card name
		randcard = 10;//set the card value
		break;
	case 'q':
		strcat(secondpart, "Queen");
		randcard = 10;
		break;
	case 'k':
		strcat(secondpart, "King");
		randcard = 10;
		break;
	case '2':
		strcat(secondpart, "2");
		randcard = 2;
		break;
	case '3':
		strcat(secondpart, "3");
		randcard = 3;
		break;
	case '4':
		strcat(secondpart, "4");
		randcard = 4;
		break;
	case '5':
		strcat(secondpart, "5");
		randcard = 5;
		break;
	case '6':
		strcat(secondpart, "6");
		randcard = 6;
		break;
	case '7':
		strcat(secondpart, "7");
		randcard = 7;
		break;
	case '8':
		strcat(secondpart, "8");
		randcard = 8;
		break;
	case '9':
		strcat(secondpart, "9");
		randcard = 9;
		break;
	case '1':
		strcat(secondpart, "10");
		randcard = 10;
		break;
	case 'a':
		strcat(secondpart, "Ace");
		if (dealer == true && yo.dealertotal <= 10) {//if it is the dealer generating a card and the dealer's value is less than or equal to 10
			randcard = 11;//dealer will have ace value of 11
			break;
		}
		else {
			if (dealer == true && yo.dealertotal > 10) {//if the dealer's value is greater than 10 then the value must be 1 or the dealer would instantly lose
				randcard = 1;
				break;
			}
		}
		if (dealer == false) {//player generating a card
			yo.acepickedplayer = true;
			if (yo.playerforme1 == true) {//program playing
				if (yo.total <= 10) {//same as dealer logic
					randcard = 11;
					break;
				}
				else {
					if (yo.total > 10) {
						randcard = 1;
						break;
					}
				}
			}
			else {// player is playing
				std::cout << "11 or 1: " << std::endl;//choice for 11 or 1 value
				while (!(std::cin >> i) || (i != 11 && i != 1)) {
					std::cin.clear();
					std::cin.ignore(1000, '\n');
					std::cout << "11 or 1: " << std::endl;
				}
				if (i == 11) {//player inputs 11
					randcard = 11;// then card value is 11
					break;
				}
				else {
					randcard = 1;// if not 11 then must be 1
					break;
				}
			}
		}
		break;
	}

	switch (randomcard[1]) {//second character of string from cards, suite of the card
	case 'd':
		strcat(secondpart, " of Diamonds");// puts the suite into the card name string
		break;
	case 's':
		strcat(secondpart, " of Spades");
		break;
	case 'c':
		strcat(secondpart, " of Clubs");
		break;
	case 'h':
		strcat(secondpart, " of Hearts");
		break;
	}
	if (donotshow == false) {// card should be shown
		std::cout << secondpart << std::endl;
		std::cout << cardarray[yo.cardsused].CardNamre;
	}
	else {
		strcat(yo.holecard, secondpart);//card shouldn't be shown so copied into holecard to be shown at start of dealer's turn
		strcat(cardarray[yo.cardsused].CardNamre, yo.holecard);
	}
	return randcard;//returns the integer randcard, this is the card value
}

int main(void)
{
	stuffs yo;
	bool restart = true;
	bool iwantquit = false;
	bool startmenu = true;
	bool hiton17 = true;
	bool gameover = false;//for the loop of a single game of blackjack
	bool showholecard = false;
	int moneytotal = 50;//total amount of money of the player
	int bet = 0;//current bet for the player
	int random_cardval;//to hold the random card's value
	int random_cardhole;//to hold the hole card's value
	int i;
	char suite[40] = "";
	struct card cardarray[312];
	int oo = 0;
	for (int g = 0; g < 4; g++) {
		if (g == 0) {
			strcpy(suite, "Spades");
		}
		else {
			if (g == 1) {
				strcpy(suite, "Diamonds");
			}
			else {
				if (g == 2) {
					strcpy(suite, "Clubs");
				}
				else {
					strcpy(suite, "Hearts");
				}
			}
		}
		for (int h = 1; h < 14; h++) {
			switch (h) {
			case 1:
				strcat(cardarray[oo].CardNamre, "10 of ");
				cardarray[oo].valuecard = 10;
				break;
			case 2:
				strcat(cardarray[oo].CardNamre, "2 of ");
				cardarray[oo].valuecard = 2;
				break;
			case 3:
				strcat(cardarray[oo].CardNamre, "3 of ");
				cardarray[oo].valuecard = 3;
				break;
			case 4:
				strcat(cardarray[oo].CardNamre, "4 of ");
				cardarray[oo].valuecard = 4;
				break;
			case 5:
				strcat(cardarray[oo].CardNamre, "5 of ");
				cardarray[oo].valuecard = 5;
				break;
			case 6:
				strcat(cardarray[oo].CardNamre, "6 of ");
				cardarray[oo].valuecard = 6;
				break;
			case 7:
				strcat(cardarray[oo].CardNamre, "7 of ");
				cardarray[oo].valuecard = 7;
				break;
			case 8:
				strcat(cardarray[oo].CardNamre, "8 of ");
				cardarray[oo].valuecard = 8;
				break;
			case 9:
				strcat(cardarray[oo].CardNamre, "9 of ");
				cardarray[oo].valuecard = 9;
				break;
			case 10:
				strcat(cardarray[oo].CardNamre, "Jack of ");//put the rank string into the string for card name
				cardarray[oo].valuecard = 10;//set the card value
				break;
			case 11:
				strcat(cardarray[oo].CardNamre, "Queen of ");
				cardarray[oo].valuecard = 10;
				break;
			case 12:
				strcat(cardarray[oo].CardNamre, "King of ");
				cardarray[oo].valuecard = 10;
				break;
			case 13:
				strcat(cardarray[oo].CardNamre, "Ace of ");
				cardarray[oo].valuecard = 11;//dealer will have ace value of 11
				break;
			}
			strcat(cardarray[oo].CardNamre, suite);
			oo++;
		}
	}
	
	while (restart == true) {//main game loop
		system("CLS");//clears console, when game restarted the console is cleared
		startmenu = true;
		while (startmenu == true) {//loop for the start menu
			std::cout << "play (1)\n" << "instructions (2)\n" << "quit (3)" << std::endl;//3 choice menu
			while ((!(std::cin >> i)) || (i != 1 && i != 2 && i != 3)) {//input not an integer or not 1,2, or 3
				std::cin.clear();//clears error flag so future inputs will work
				std::cin.ignore(1000, '\n');//skips to next line to ignore any failures
				std::cout << "(fail) play (1)\n" << "instructions (2)\n" << "quit (3)" << std::endl;
			}
			if (i == 3) {//quit
				std::cout << "End game? yes(1) or no(2) " << std::endl;
				while ((!(std::cin >> i)) || (i != 1 && i != 2)) {
					std::cin.clear();
					std::cin.ignore(1000, '\n');
					std::cout << "(fail) End game? yes(1) or no(2) " << std::endl;
				}
				if (i == 1) {//yes
					exit(0);
				}
				else {//no
					startmenu = true;
					system("CLS");
				}
			}
			else {
				if (i == 2) {//instructions
					std::cout << "The goal of blackjack is to beat the dealer's hand without going over 21." << std::endl;
					std::cout << "Face cards are worth 10. Aces are worth 1 or 11, whichever makes a better hand." << std::endl;
					std::cout << "Each player starts with two cards, one of the dealer's cards is hidden until the end." << std::endl;
					std::cout << "To 'Hit' is to ask for another card. To 'Stand' is to hold your total and end your turn." << std::endl;
					std::cout << "If you go over 21 you bust, and the dealer wins regardless of the dealer's hand." << std::endl;
					std::cout << "If you are dealt 21 from the start (Ace & 10), you got a blackjack." << std::endl;
					std::cout << "Blackjack usually means you win 1.5 the amount of your bet. Depends on the casino." << std::endl;
					std::cout << "Dealer will hit until his/her cards total 17 or higher." << std::endl;
					std::cout << "Doubling is like a hit, only the bet is doubled and you only get one more card." << std::endl;
					std::cout << "You can only double on the first move \n" << std::endl;
					startmenu = true;
				}// examples????
				else {//play
					startmenu = false;//breaks start menu loop
				}
			}
		}

		system("CLS");
		yo.cardsused = 0;//new game so cardsused will be 0

		std::cout << "How many decks? 1 or 2 or 6: ";// NEED TO CHANGE SHUFFLE?? AND CARDSUSED FOR SHUFFLE ??
		while ((!(std::cin >> i)) || (i != 1 && i != 2 && i != 6)) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "(fail) How many decks? 1 or 2 or 6: ";
		}
		if (i == 1) {
			yo.onecards = true;
			yo.twocards = false;
			yo.sixcards = false;
		}
		else {
			if (i == 2) {
				yo.twocards = true;
				yo.onecards = false;
				yo.sixcards = false;
			}
			else {
				if (i == 6) {
					yo.sixcards = true;
					yo.onecards = false;
					yo.twocards = false;
				}
			}
		}

		int n = 0;
		
		for (int i = 311; i > 51; i--) {
			strcpy(yo.cards[i], "\0");
			strcpy(cardarray[i].CardNamre, "\0");
		}
		if (yo.onecards == true) {
			n = 0;
		}
		else {
			if (yo.twocards == true) {
				n = 52;
			}
			else {
				n = 260;
			}
		}
		for (i = 0; i < n; i++) {
			strcpy(yo.cards[i + 52], yo.cards[i]);
			strcpy(cardarray[i + 52].CardNamre, cardarray[i].CardNamre);
			cardarray[i + 52].valuecard = cardarray[i].valuecard;
		}

		std::cout << "Play for you? yes (1) or no (2): ";
		while ((!(std::cin >> i)) || (i != 1 && i != 2)) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "(fail) Play for you? yes (1) or no (2): ";
		}
		if (i == 1) {//yes
			yo.playerforme1 = true;
		}
		else {//no
			yo.playerforme1 = false;
		}

		std::cout << "Dealer hits on 17? yes (1) or no (2): ";
		while ((!(std::cin >> i)) || (i != 1 && i != 2)) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "(fail) Dealer hits on 17? yes (1) or no (2): ";
		}
		if (i == 1) {//yes
			hiton17 = true;
		}
		else {//no
			hiton17 = false;
		}
		system("CLS");

		shuffle(yo, cardarray);//shuffle cards 20 times
		iwantquit = false;
		moneytotal = 50;

		while (moneytotal > 0 && iwantquit == false)//more than 0 money and player has not chosen to quit game
		{
			bet = 0;
			yo.total = 0;//player's card value starts at 0
			yo.dealertotal = 0;//dealer's card value starts at 0
			gameover = false;//this can be made true before loop starts (blackjack), so need to be at start - default is that the loop is entered
			showholecard = false;//auto don't show
			yo.acepickedplayer = false;//program has drawn an ace - changes probabilites

			std::cout << "Money total: " << moneytotal << std::endl;//player's money
			std::cout << "how much do yo want to bet: ";

			while ((!(std::cin >> bet)) || (bet > moneytotal || bet < 1)) {//is an int and is less than player's money total and bigger than 0
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				std::cout << "(fail) how much do yo want to bet: ";
			}

			//STAND OR HIT ON SOFT 17

			std::cout << "Display dealer's hole card? yes (1) or no (2): ";
			while ((!(std::cin >> i)) || (i != 1 && i != 2)) {
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				std::cout << "(fail) Display dealer's hole card? yes (1) or no (2): ";
			}
			if (i == 1) {//yes
				showholecard = true;
			}
			else {//no
				showholecard = false;
			}

			system("CLS");

			//Sleep(2000);

			random_cardval = random_card(false, false, yo, cardarray);//generate a random card and return card value which is set to int random_cardval
			yo.total += random_cardval;//player's total card value increased by value of the generated card

			//Sleep(1000);

			random_cardval = random_card(false, false, yo, cardarray);
			yo.total += random_cardval;

			std::cout << "\n" << "Your draw value: " << yo.total << "\n" << std::endl;
			std::cout << "dealer's go \n" << std::endl;

			//Sleep(2000);

			random_cardval = random_card(true, false, yo, cardarray);//generate a random card for the dealer; no ace choice
			yo.dealertotal += random_cardval;//dealer's total card value increased by value of the generated card

			//Sleep(1000);

			if (showholecard == true) {//based on player's earlier decision
				random_cardhole = random_card(true, false, yo, cardarray);//show hole card
				std::cout << "\n" << "Dealer draw value: " << yo.dealertotal << " and " << yo.holecard << "\n" << std::endl;
			}
			else {
				random_cardhole = random_card(true, true, yo, cardarray);//dont show hole card
				std::cout << "hole card" << std::endl;
				std::cout << "\n" << "Dealer draw value: " << yo.dealertotal << " and the hole card\n" << std::endl;
			}

			std::cout << "Your total: " << yo.total << "\t Dealer total: " << yo.dealertotal << "\n" << std::endl;

			if (yo.total == 21) {// if player has perfect blackjack
				std::cout << "hole card\n" << yo.holecard << std::endl;//dealer must show hole card
				yo.dealertotal += random_cardhole;
				std::cout << "Your total: " << yo.total << "\t Dealer total: " << yo.dealertotal << "\n" << std::endl;
				if (yo.dealertotal != 21) {//dealer lost
					std::cout << "BLACKJACK || you win" << std::endl;
					moneytotal += (bet + (bet / 2));
					gameover = true;//game loop doesn't run
				}
			}
			bool sord = false;//when the player has stood
			bool dooble = false;//whether double can be used or not
			bool dooblemoney = false;//if the player has doubled they get double the money
			char winlosedraw = '$';//whether the player has won, lost or drawn; W, w, d, l - big W is for double win

			while (gameover == false) {//game loop
				int hitorstay = 0;//hit or stay or double decision
				if (yo.playerforme1 == true && dooble == false) {//program player can double
					if (yo.acepickedplayer == false) {//no ace picked up by program player
						switch (yo.dealertotal) { // depending on dealer's value; pre defined whether to hit stay or double based on parameters on player's value
						case 2:
							if (yo.total < 13) {
								hitorstay = 1;
								if (yo.total == 11) {
									hitorstay = 3;
								}
							}
							else {
								hitorstay = 2;
							}
							break;
						case 3:
							if (yo.total < 13) {
								hitorstay = 1;
								if (yo.total == 11) {
									hitorstay = 3;
								}
							}
							else {
								hitorstay = 2;
							}
							break;
						case 4:
							if (yo.total < 10) {
								hitorstay = 1;
							}
							else {//fine
								if (yo.total == 10 || yo.total == 11) {
									hitorstay = 3;
								}
								else {
									hitorstay = 2;
								}
							}
							break;
						case 5:
						case 6:
							if (yo.total < 9) {
								hitorstay = 1;
							}
							else {//fine
								if (yo.total == 9 || yo.total == 10 || yo.total == 11) {
									hitorstay = 3;
								}
								else {
									hitorstay = 2;
								}
							}
							break;
						case 7:
						case 8:
						case 9:
						case 10:
							if (yo.total < 17) {
								hitorstay = 1;
								if (yo.total == 11) {
									hitorstay = 3;
								}
							}
							else {
								hitorstay = 2;
							}
							break;

						case 11:
							if (yo.total < 18) {
								hitorstay = 1;
								if (yo.total == 11) {
									hitorstay = 3;
								}
							}
							else {
								hitorstay = 2;
							}
							break;
						}
					}
					else {//picked up an ace
						switch (yo.dealertotal) {
						case 2:
							if (yo.total < 19) {
								hitorstay = 1;
							}
							else {
								hitorstay = 2;
							}
							break;
						case 3:
							if (yo.total < 17) {
								hitorstay = 1;
							}
							else {
								if (yo.total == 17) {
									hitorstay = 3;
								}
								else {
									hitorstay = 2;
								}
							}
							break;
						case 4:
							if (yo.total < 15) {
								hitorstay = 1;
							}
							else {//fine
								if (yo.total == 15 || yo.total == 16 || yo.total == 17) {
									hitorstay = 3;
								}
								else {
									hitorstay = 2;
								}
							}
							break;
						case 5:
						case 6:
							if (yo.total < 19) {
								hitorstay = 3;
							}
							else {
								hitorstay = 2;
							}
							break;
						case 7:
						case 8:
							if (yo.total < 18) {
								hitorstay = 1;
							}
							else {
								hitorstay = 2;
							}
							break;
						case 9:
						case 10:
						case 11:
							if (yo.total < 19) {
								hitorstay = 1;
							}
							else {
								hitorstay = 2;
							}
							break;
						}
					}
				}
				else {
					if (yo.playerforme1 == true && dooble == true) {//can't double
						if (yo.acepickedplayer == false) {
							switch (yo.dealertotal) {
							case 2:
								if (yo.total < 13) {
									hitorstay = 1;
								}
								else {
									hitorstay = 2;
								}
								break;
							case 3:
								if (yo.total < 13) {
									hitorstay = 1;
								}
								else {
									hitorstay = 2;
								}
								break;
							case 4:
								if (yo.total < 13) {
									hitorstay = 1;
								}
								else {
									hitorstay = 2;
								}
								break;
							case 5:
							case 6:
								if (yo.total < 13) {
									hitorstay = 1;
								}
								else {
									hitorstay = 2;
								}
								break;
							case 7:
							case 8:
							case 9:
							case 10:
								if (yo.total < 17) {
									hitorstay = 1;
								}
								else {
									hitorstay = 2;
								}
								break;

							case 11:
								if (yo.total < 18) {
									hitorstay = 1;
								}
								else {
									hitorstay = 2;
								}
								break;
							}
						}
						else {
							switch (yo.dealertotal) {
							case 2:
								if (yo.total < 19) {
									hitorstay = 1;
								}
								else {
									hitorstay = 2;
								}
								break;
							case 3:
								if (yo.total < 17) {
									hitorstay = 1;
								}
								else {
									hitorstay = 2;
								}
								break;
							case 4:
								if (yo.total < 18) {
									hitorstay = 1;
								}
								else {
									hitorstay = 2;
								}
								break;
							case 5:
							case 6:
								if (yo.total < 19) {
									hitorstay = 1;
								}
								else {
									hitorstay = 2;
								}
								break;
							case 7:
							case 8:
								if (yo.total < 18) {
									hitorstay = 1;
								}
								else {
									hitorstay = 2;
								}
								break;
							case 9:
							case 10:
							case 11:
								if (yo.total < 19) {
									hitorstay = 1;
								}
								else {
									hitorstay = 2;
								}
								break;
							}
						}
					}
				}
				if (yo.playerforme1 == false) {//user playing not program
					if (dooble == false) {//player can double; first action
						std::cout << "Hit (1) \n" << "Stay (2) \n" << "Double (3) \n" << std::endl;
					}
					else {//player can't double; past first action
						std::cout << "Hit (1) \n" << "Stay (2) \n" << std::endl;
					}
					while ((!(std::cin >> hitorstay)) || (hitorstay != 1 && hitorstay != 2 && hitorstay != 3)) {
						std::cin.clear();
						std::cin.ignore(1000, '\n');
						if (dooble == false) {
							std::cout << "Hit (1) \n" << "Stay (2) \n" << "Double (3) \n" << std::endl;
						}
						else {
							std::cout << "Hit (1) \n" << "Stay (2) \n" << std::endl;
						}
					}
					std::cout << std::endl;
				}
				if (hitorstay == 3 && dooble == false) {//double and the player is able to double; first action
					sord = true;//can't hit anymore, goes to stand loop
					dooble = true;//can't double again
					dooblemoney = true;//player will get double money if they win
					std::cout << "PLAYER HIT (DOUBLE)\n" << std::endl;
					random_cardval = random_card(false, false, yo, cardarray);
					yo.total += random_cardval;
					std::cout << "Your total: " << yo.total << "\t Dealer total: " << yo.dealertotal << "\n" << std::endl;
					if (yo.total > 21) {//bust
						winlosedraw = 'l';
						sord = false;
					}
					if (yo.total == 21) {
						sord = true;
						//Sleep(1000);
					}
				}
				else {
					if (hitorstay == 2) {//stay
						sord = true;
						if (yo.dealertotal > yo.total) {//already lost
							winlosedraw = 'l';
							sord = false;
						}
					}
					else {
						if (hitorstay == 1) {//hit
							dooble = true;//can't double anymore
							std::cout << "PLAYER HIT\n" << std::endl;
							//Sleep(2000);
							random_cardval = random_card(false, false, yo, cardarray);//hit
							yo.total += random_cardval;
							std::cout << "Your total: " << yo.total << "\t Dealer total: " << yo.dealertotal << "\n" << std::endl;
							if (yo.total > 21) {//bust
								winlosedraw = 'l';
								sord = false;
							}
							if (yo.total == 21) {
								sord = true;
								//Sleep(1000);
							}
						}
					}
				}
				if (sord == true) {
					std::cout << "\nTHE PLAYER HAS STOOD\n\n" << std::endl;
					//Sleep(2000);
					std::cout << "DEALER'S HOLE CARD\n" << yo.holecard << std::endl;//showing hole card
					yo.dealertotal += random_cardhole;//adding previously generate hole card value to dealer's total
					std::cout << "Your total: " << yo.total << "\t Dealer total: " << yo.dealertotal << "\n" << std::endl;
					//yo.dealertotal = 16;//TESTING VALUES
					//yo.total = 16;
					//std::cout << "Your total: " << yo.total << "\t Dealer total: " << yo.dealertotal << "\n" << std::endl;

					if (hiton17 == true) {
						while ((yo.dealertotal < yo.total && yo.dealertotal < 21) || (yo.dealertotal <= yo.total && yo.total < 17)) {//dealer total is less than equal to player's total and dealer total is less than 21; until player wins, loses or draws
							std::cout << "DEALER HIT\n" << std::endl;
							//Sleep(2000);
							random_cardval = random_card(true, false, yo, cardarray);
							yo.dealertotal += random_cardval;
							std::cout << "Your total: " << yo.total << "\t Dealer total: " << yo.dealertotal << "\n" << std::endl;
						}
					}
					else {
						if (hiton17 == false) {
							while ((yo.dealertotal < yo.total && yo.dealertotal < 17) || (yo.dealertotal <= yo.total && yo.total < 17)) {
								std::cout << "DEALER HIT\n" << std::endl;
								//Sleep(2000);
								random_cardval = random_card(true, false, yo, cardarray);
								yo.dealertotal += random_cardval;
								std::cout << "Your total: " << yo.total << "\t Dealer total: " << yo.dealertotal << "\n" << std::endl;
							}
						}
					}

					if ((yo.dealertotal < 21 && ((yo.dealertotal > yo.total) || yo.total > 21)) || (yo.dealertotal == 21 && yo.total != 21)) {//loss
						winlosedraw = 'l';
					}
					else {
						if ((yo.total < 21 && ((yo.total > yo.dealertotal) || yo.dealertotal > 21)) || (yo.dealertotal != 21 && yo.total == 21)) {//win
							if (dooblemoney == true) {
								winlosedraw = 'W';
							}
							else {
								winlosedraw = 'w';
							}
						}
						else {
							if (yo.dealertotal == yo.total && yo.dealertotal >= 17) {//draw
								winlosedraw = 'd';
							}
						}
					}
				}
				switch (winlosedraw) {//game result
				case 'w'://win
					std::cout << "(w)you win" << std::endl;
					moneytotal += bet;
					gameover = true;
					break;
				case 'W'://double win
					std::cout << "(W)you win" << std::endl;
					moneytotal += bet * 2;
					gameover = true;
					break;
				case 'l'://lose
					std::cout << "(l)you lose" << std::endl;
					moneytotal -= bet;
					gameover = true;
					break;
				case 'd'://draw
					std::cout << "(d)draw" << std::endl;
					moneytotal = moneytotal;
					gameover = true;
					break;
				}
			}
			for (i = 0; i < 40; i++) {
				yo.holecard[i] = '\0';// set string to just null characters
			}
			std::cout << "Money total: " << moneytotal << std::endl;
			if (moneytotal <= 0) {// if the player has 0 or less money
				std::cout << "no money, you lose" << "\n" << "\n" << std::endl;
				system("pause");
				restart = true;// restart game
			}
			else {//continue, NOT NEEDED
				restart = false;
			}
			if (restart == false) {
				std::cout << "End game? yes(1) or no(2) " << std::endl;
				while ((!(std::cin >> i)) || (i != 1 && i != 2)) {
					std::cin.clear();
					std::cin.ignore(1000, '\n');
					std::cout << "(fail) End game? yes(1) or no(2) ";
				}
				if (i == 1) {//yes
					iwantquit = true;//restart game
					restart = true;
				}
				else {//no
					iwantquit = false;//continue with current game
					system("CLS");
				}
			}
		}
	}
	return 0;
}