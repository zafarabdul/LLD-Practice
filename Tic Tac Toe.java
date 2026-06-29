import java.util.*;
//Tic Tac Toe LLD
//game
//Board
//Players
//winningStrategt

interface Player{
    char getSymbol();
}

class PlayerA implements Player{
    private char symbol = 'O';

    public char getSymbol(){
        return symbol;
    }
}

class PlayerB implements Player{
    private char symbol = 'X';

    public char getSymbol(){
        return symbol;
    }
}

abstract class WinningStrategy {
    public abstract boolean didWin(Board b, char c);
}

class WinningByRow extends WinningStrategy{
    public boolean didWin(Board b, char c){
        ArrayList<ArrayList<Character>> mat = b.getArray();

        for(int i=0;i<mat.size();i++){
            boolean row = true;

            for(int j=0;j<mat.get(0).size();j++){
                row = row & (mat.get(i).get(j)==c);
            }

            if(row)return true;
        }

        return false;
    }
}

class WinningByColumn extends WinningStrategy{
    public boolean didWin(Board b, char c){
        ArrayList<ArrayList<Character>> mat = b.getArray();

        for(int i=0;i<mat.size();i++){
            boolean row = true;

            for(int j=0;j<mat.get(0).size();j++){
                row = row & (mat.get(j).get(i)==c);
            }

            if(row)return true;
        }

        return false;
    }
}

class WinningByDiagonal extends WinningStrategy{
    public boolean didWin(Board b, char c){
        ArrayList<ArrayList<Character>> mat = b.getArray();

        boolean d1 = true;
        boolean d2 = true;

        for(int i=0;i<mat.size();i++){
            d1 = d1 & (mat.get(i).get(i)==c);
            d2 = d2 & (mat.get(i).get(mat.size()-i-1)==c);

            if(!d1 && !d2)return false;
        }

        return true;
    }
}

class Board{
    private ArrayList<ArrayList<Character>> mat = new ArrayList<ArrayList<Character>>();

    public Board(){
        mat.add(new ArrayList<>(Arrays.asList('-', '-', '-')));
        mat.add(new ArrayList<>(Arrays.asList('-', '-', '-')));
        mat.add(new ArrayList<>(Arrays.asList('-', '-', '-')));
    }

    public ArrayList<ArrayList<Character>> getArray(){
        return mat;
    }

    public boolean mark(int i,int j,char sym){
        if(mat.get(i-1).get(j-1) != '-'){
            System.out.println("Already Marked");
            return false;
        }

        mat.get(i-1).set(j-1,sym);
        return true;
    }

    public void printBoard(){
        for(var i:mat){
            for(var j:i){
                System.out.print(j);
            }
            System.out.println();
        }
        System.out.println("___________________________________________________");
    }
}

class Game{
    private Player A = null;
    private Player B = null;
    private Board board = null;
    private char turn = 'A';

    public Game(){
        A = new PlayerA();
        B = new PlayerB();
        board = new Board();
    }

    private void checkWin(char p,char c){
        WinningStrategy w1 = new WinningByRow();
        WinningStrategy w2 = new WinningByColumn();
        WinningStrategy w3 = new WinningByDiagonal();

        if( w1.didWin(board,c) || w2.didWin(board,c) || w3.didWin(board,c) ){
            System.out.println("Game Over");
            System.out.println(p +" - Won");
        }
    }

    public void markByA(int i,int j){
        if(turn != 'A'){
            System.out.println("It's B's Turn");
            return;
        }

        if(board.mark(i , j , A.getSymbol())){
            checkWin('A' ,  A.getSymbol());
            turn = 'B';
        }
        board.printBoard();
    }

    public void markByB(int i,int j){
        if(turn != 'B'){
            System.out.println("It's A's Turn");
            return;
        }

        if(board.mark(i , j , B.getSymbol())){
            checkWin('B' ,  B.getSymbol());
            turn = 'A';
        }
        board.printBoard();
    }

    public void printBoard(){
        board.printBoard();
    }
}

class Main {
    public static void main(String[] args) {
        Game g1 = new Game();

        g1.markByA(1,1);
        g1.markByA(1,1);
        // print b's turn
        g1.markByB(1,1);
        // print already marked
        g1.markByB(3,2);
        
        g1.markByA(2,2);
        g1.markByB(3,1);
        g1.markByA(3,3);
        // g1.printBoard();
    }
}
