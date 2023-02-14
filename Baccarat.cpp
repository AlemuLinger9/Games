#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
// To control the size of the shoe.
// Each card symbol in the 8 deck size shoe have an ammount of 32.
// Here I assume the suits of the card doesn't have any effect in the game. 
int shoe[2][13] = {{1,2,3,4,5,6,7,8,9,10,11,12,13},{32,32,32,32,32,32,32,32,32,32,32,32,32}};
// The following function is used to fill the shoe if it is empty. 
void fillShoe(){
	for(int i = 1; i <= 13; i++){
		shoe[0][i] = i;
		shoe[1][i] = 32;
	}
}
// The below function contains the core of the game. It produces a random card whenever the players need a new card.
// I consider the random choose as a shuffling.
int getCard(){
	int index = -1;
	bool getNewCard = false;
	int shoeSize = 0;
	for(int i = 0; i<13; i++){
		shoeSize=+shoe[1][i];
	}
	if(shoeSize==0){
	  fillShoe();
	}
	tryAgain:
	index = rand()%13;
	int newCard = shoe[0][index];
	while(!getNewCard){
	    if(shoe[1][index]>=1){
			getNewCard = true;
			shoe[1][index]=shoe[1][index]-1;
			break;
		}
		else{
			goto tryAgain;
		}
	}
	return newCard;
}
// The below function determines the result of the players hand.
int getPlayer(int pcard1, int pcard2){
	int choice1 = pcard1;
	int choice2 = pcard2;
	if(pcard1>=10)
	choice1 = pcard1 - pcard1;
	if(pcard2>=10)
	choice2 = pcard2 - pcard2;
	int result = (choice1+choice2)%10;
	return result;
}
// The below function determines the result of the bankers hand.
int getBanker(int bcard1, int bcard2){
	int choice1 = bcard1;
	int choice2 = bcard2;
	if(bcard1>=10)
	choice1 = bcard1-bcard1;
	if(bcard2>=10)
	choice2 = bcard2-bcard2;
	int result = (choice1+choice2)%10;
	return result;
}
int main(){
	srand ( time(NULL) );
    int pcard1 = getCard(); // gets a new card from the shoe containing shuffled cards.
    int bcard1 = getCard();
	int pcard2 = getCard();
	int bcard2 = getCard();
	int player = getPlayer(pcard1,pcard2);
	int banker = getBanker(bcard1, bcard2);
	int pcard3 = 0;
	int bcard3 = 0;
	bool p3rd = false;
	bool b3rd = false;
	string outcome = "";
	
	if(player==banker){
	   goto output;
	}
	else if((player==8||player==9)||(banker==9||banker==8)){
		goto output;
	}
	else{
		if(player==6||player ==7){
			player = player;
			if(banker==6||banker==7){
				banker = banker;
			}
			else{
				bcard3 = getCard();
				b3rd = true;
				banker = getBanker(banker, bcard3);
				goto output;
			}
		}
		else{
		    pcard3 = getCard();
		    p3rd = true;
			player = getPlayer(player,pcard3);
			if(banker<=2){
				bcard3 = getCard();
				b3rd = true;
				banker = getBanker(banker, bcard3);
				goto output;
			}
			else if(banker == 3){
				if(pcard3!=8){
					bcard3 = getCard();
					b3rd = true;
				    banker = getBanker(banker, bcard3);
				    goto output;
				}
				else{
					goto output;
				}	
			}
			else if(banker == 4){
				if(pcard3==0||pcard3==1||pcard3==8||pcard3==9){
					goto output;
				}
				else{
					bcard3 = getCard();
					b3rd = true;
				    banker = getBanker(banker, bcard3);
				    goto output;
				}
			}
			else if(banker==5){
				if(pcard3==4||pcard3==5||pcard3==6||pcard3==7){
					bcard3 = getCard();
					b3rd = true;
				    banker = getBanker(banker, bcard3);
				    goto output;
				}
				else{
					goto output;
				}
			}
			else if(banker == 6){
				if(pcard3==6||pcard3==7){
					bcard3 = getCard();
					b3rd = true;
				    banker = getBanker(banker, bcard3);
				    goto output;
				}
				else{
					goto output;
				}
				
			}
			else{
				goto output;
			}
		}
	}
	output:
	if(player>banker)
	outcome = "Player";
	else if(player<banker)
	outcome = "Banker";
	else
	outcome = "Tie";
	cout<<"PHand  -  BHand  -  Outcome\n";
	if(b3rd && p3rd){
		cout<<pcard1<<", "<<pcard2<<", "<<pcard3<<"   -  ";
	    cout<<bcard1<<", "<<bcard2<<", "<<bcard3<<"   -  ";
	}
else if(p3rd){
	cout<<pcard1<<", "<<pcard2<<", "<<pcard3<<"   -  ";
	cout<<bcard1<<", "<<bcard2<<"  -  ";
}
else if(b3rd){
	cout<<pcard1<<", "<<pcard2<<"   - ";
	cout<<bcard1<<", "<<bcard2<<", "<<bcard3<<"   -  ";
}
else{
	cout<<pcard1<<", "<<pcard2<<"   -  ";
	cout<<bcard1<<", "<<bcard2<<"   -  ";
}
	cout<<outcome;
	return 0;
}
