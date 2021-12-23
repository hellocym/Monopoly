#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

int RollDice(int sides)
{
    int roll;
    roll = rand() % sides + 1;
    return roll;
}

int SelectMode(){
    int mode = 0;
    while(1){
        printf("选择模式：\n1.单人模式\n2.双人模式\n");
        scanf("%d",&mode);
        if(mode != 1 && mode != 2){
            printf("输入错误，请重新输入\n");
            continue;
        }
        printf("您选择了%d\n",mode);
        return mode;
    }
}

int SelectMapSize(){
    int size = 0;
    while(1){
        printf("请选择地图大小：\n1.小地图\n2.大地图\n");
        scanf("%d",&size);
        if(size != 1 && size != 2){
            printf("输入错误，请重新输入\n");
            continue;
        }
        if(size == 1){
            printf("您选择了小地图\n");
            return 11;
        }
        else{
            printf("您选择了大地图\n");
            return 40;
        }
    }
}

int chance(){
    // 抽取机会卡
    switch(RollDice(6)){
        case 1:
            printf("您看病花了 200 点\n");
            return -200;
        case 2:
            printf("您投资赚了 400 点\n");
            return 400;
        case 3:
            printf("您花费 600 点买了一栋房\n");
            return -600;
        case 4:
            printf("您收了 300 点房租\n");
            return 300;
        case 5:
            printf("您嫖娼被抓，罚款 200 点\n");
            return -200;
        case 6:
            printf("您打车出游花费 100 点\n");
            return -100;
    }
}

int Event(int location, int mapSize, int money, int mode, int player){
    char playerName[20] = "";
    if(mode == 1){
        if(player == 1){
            strcat(playerName,"您");
        }
        else{
            strcat(playerName,"对手");
        }
    }
    else{
        if(player == 1){
            strcat(playerName,"玩家1");
        }
        else{
            strcat(playerName,"玩家2");
        }
    }
    if(mapSize == 11){
        // 小地图
        switch(location){
            case 2:
                printf("%s看病花了 200 点\n", playerName);
                return -200;
            case 4:
                printf("%s投资赚了 400 点\n", playerName);
                return 400;
            case 6:
                printf("%s花费 600 点买了一栋房\n", playerName);
                return -600;
            case 7:
                printf("%s收了 300 点房租\n", playerName);
                return 300;
            case 9:
                printf("%s嫖娼被抓，罚款 200 点\n", playerName);
                return -200;
            case 10:
                printf("%s打车出游花费 100 点\n", playerName);
                return -100;   
            default:
                return 0;
        }
    }
    if(mapSize == 40){
        // 大地图
        if(location == 0){
            printf("%s现在在起点，您获得 200 点奖励\n", playerName);
            return 200;
        }
        else if(location == 2 || location == 17 || location == 33){
            printf("%s现在在社会基金格，您获得 100 点奖励\n", playerName);
            return 100;
        }
        else if(location == 7 || location == 22 || location == 36){
            printf("%s现在在机会格，抽取机会卡\n", playerName);
            return chance();
        }
        else if(location == 30 || location == 5){
            printf("%s现在在监狱，需付 50 点出狱\n", playerName);
            return -50;
        }
        else if(location == 4 || location == 38){
            printf("%s现在在所得税格，需付 3%% 的点数 \n", playerName);
        }
        else if(location == 10 || location == 20){
            printf("%s现在在奢侈品税格，需付 10%% 的点数 \n", playerName);
            return -money*0.1;
        }
    }
    return 0;
}

int Game(int mapSize, int mode){
    int dice = 0;
    int loc1 = 0;
    int loc2 = 0;
    int money1 = 1500;
    int money2 = 1500;
    int round = 0;
    int currentRound = 0;
    char player1[20] = "您";
    char player2[20] = "对手";
    if(mode == 2){
        strcpy(player1, "玩家1");
        strcpy(player2, "玩家2");
    }
    printf("请输入游戏轮数\n");
    scanf("%d",&round);
    printf("游戏开始\n");
    getchar();
    printf("%s的起始位置是 0 号格\n", player1);
    printf("%s的起始位置是 0 号格\n", player2);
    printf("%s的起始金钱是 1500 点\n", player1);
    printf("%s的起始金钱是 1500 点\n", player2);
    currentRound = 1;
    while(currentRound <= round){
        printf("\n现在是第%d轮\n", currentRound);

        // 玩家1回合
        printf("现在是%s的回合\n", player1);
        printf("按任意键掷骰子\n");
        getchar();
        dice = RollDice(6);
        printf("%s掷出了 %d 点\n", player1, dice);
        loc1 += dice;
        if(loc1 >= mapSize){
            loc1 -= mapSize;
        }
        printf("%s现在在 %d 号格\n", player1, loc1);
        money1 += Event(loc1, mapSize, money1, mode, 1);
        printf("%s现在的金钱是 %d 点\n\n", player1, money1);
        if(money1 < 0){
            printf("%s破产了，游戏结束\n", player1);
            return 0;
        }

        // 玩家2回合
        printf("现在是%s的回合\n", player2);
        if(mode == 2){
            printf("按任意键掷骰子\n");
            getchar();
        }
        dice = RollDice(6);
        printf("%s掷出了 %d 点\n", player2, dice);
        loc2 += dice;
        if(loc2 >= mapSize){
            loc2 -= mapSize;
        }
        printf("%s现在在 %d 号格\n", player2, loc2);
        money2 += Event(loc2, mapSize, money2, mode, 2);
        printf("%s现在的金钱是 %d 点\n\n", player2, money2);

        if(money2 < 0){
            printf("%s破产了，游戏结束\n", player2);
            return 1;
        }

        currentRound++;
    }
    return (money1 > money2);
    // true 表示玩家1赢
    // false 表示玩家2赢
}

int main(){
    int mode = SelectMode();
    int mapSize = SelectMapSize();
    int player1Wins = Game(mapSize, mode);
    srand((unsigned)time(NULL));
    char player1[20] = "您";
    char player2[20] = "对手";
    if(mode == 2){
        strcpy(player1, "玩家1");
        strcpy(player2, "玩家2");
    }
    if(player1Wins){
        printf("%s赢了\n", player1);
    }
    else{
        printf("%s赢了\n", player2);
    }
    return 0;
}
