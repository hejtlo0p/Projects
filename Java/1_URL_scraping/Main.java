/*  Project:    Book of Mormon guessing verse game
*   Created by: Peter Stegeby
*   Created:    2021-08-18
*   Modified:   2021-08-19
*   Info:       This program scrapes the content from ChurchOfJesusChrist Book of mormon and stores
*               the verses in vectors in order to work with it. The player get 5 verses that he/she can
*               guess the book, chapter and the verse from the Book of Mormon. Guessing book will grant
*               some points, guess the chapter will grant more points and guessing the verse, with some
*               verses give or take, will grant the most points. May the odds be ever in your favor!
*
* Ideas:        Add hints, can read next verse for a small penalty, up to three hints.
 */

import java.util.Random;
import java.util.Scanner;

public class Main {
    private static final int[] chapters = {22, 33, 7, 1, 1, 1, 1, 29, 63, 16, 30, 1, 9, 15, 10};
    private static final String[] books = {"1 Nephi", "2 Nephi", "Jakob", "Enos", "Jarom", "Omni", "Mormons ord", "Mosiah", "Alma", "Helaman", "3 Nephi", "4 Nephi", "Mormon", "Ether", "Moroni"};

    private static String bookName;
    private static int verseGuess;
    private static double points = 0;
    private static double tempPoints = 0;

    public static void main(String[] args) {

        int tries = 0;

        while (tries < 5) {
            tempPoints = 0;
            Book b = randomBook();
            Chapter c = b.getBook().get(0);
            String s = c.generateRandomVerse();
            printString(s);
            playGame(b, c);
            System.out.printf("[%s] Gammal: %s, Tillagd: %s, Ny: %s%n", tries+1, (points - tempPoints), tempPoints, points);
            tries++;
        }

        System.out.println("Points: " + points);

    }

    public static Book randomBook() {
        Random ran = new Random();
        int num = 0;
        try {
            num = ran.nextInt(books.length);
            bookName = books[num];
            return new Book(books[num], chapters[num]);
        }
        catch (ArrayIndexOutOfBoundsException ex) {
            System.err.println(ex + "num: " + num);
            return new Book();
        }
    }

    public static void printChapter(Chapter c) {
        int i = 1;
        for (String s : c.getChapter()) {
            System.out.println(i + " " + s);
            i++;
        }
    }

    public static void printBook(Book b) {
        int i = 1;
        for(Chapter c : b.getBook()) {
            System.out.println("\nKapitel: " + i);
            int j = 1;
            for(String s : c.getChapter()) {
                System.out.println(j + " " + s);
                j++;
            }
            i++;
        }
    }

    public static void printString(String s) {
        char[] arr = s.toCharArray();
        int space = 0;
        System.out.println("\nVers: ");
        for (char c : arr) {
            if (c == ' ') {
                space++;
            }

            if (space > 10) {
                System.out.println();
                space = 0;
            }
            else {
                System.out.print(c);
            }
        }
        System.out.println("\n***********");
    }

    public static boolean guessVerse(Chapter c) {
        Scanner scanner = new Scanner(System.in);
        System.out.printf("Vilken Vers är detta? (1-%s) >", c.getVerses());
        verseGuess = scanner.nextInt();
        return verseGuess == c.getRandVers();
    }

    public static boolean guessChapter(Book b) {
        int guess;
        Scanner scanner = new Scanner(System.in);
        System.out.printf("Vilket kapitel är detta? (1-%s) >", b.getChapters());
        guess = scanner.nextInt();
        return guess == b.getRandChapter();
    }

    public static boolean guessBook() {
        String guess;
        Scanner scanner = new Scanner(System.in);
        System.out.print("Vilken bok är detta? >");
        guess = scanner.nextLine();
        return guess.equalsIgnoreCase(bookName);
    }

    public static void playGame(Book o, Chapter c) {
        boolean guess = guessBook();
        int point = 4;
        if (guess) {
            System.out.println("Grattis, Det var rätt bok!");
            points += point * 1.25;
            tempPoints += point * 1.25;
            guess = guessChapter(o);
            if (guess) {
                System.out.println("Grattis, Det var rätt kapitel!");
                points += point * 2.75;
                tempPoints += point * 2.75;
                guess = guessVerse(c);
                if (guess) {
                    System.out.println("Grattis, Det var rätt vers!");
                    points += point * 8.25;
                    tempPoints += point * 8.25;
                }
                else {
                    int difference = Math.abs(c.getRandVers() - verseGuess);
                    if (difference <= 3) {
                        System.out.printf("[FEL VERS] Nära! [%s] ifrån! Rätt svar var %s %s:[%s].%n", difference, bookName, o.getRandChapter(), c.getRandVers());
                        points += point * 5.25;
                        tempPoints += point * 5.25;
                    }
                    else if (difference <= 8) {
                        System.out.printf("[FEL VERS] Det var en bra gissning! [%s] ifrån! Rätt svar var %s %s:[%s].%n", difference, bookName, o.getRandChapter(), c.getRandVers());
                        points += point * 3.25;
                        tempPoints += point * 3.25;
                    }
                    else {
                        System.out.printf("[FEL VERS] Osis, rätt svar var %s %s:[%s], bättre lycka nästa gång!%n", bookName, o.getRandChapter(), c.getRandVers());
                    }
                }
            }
            else {
                System.out.printf("[FEL KAPITEL] Osis, rätt svar var %s [%s:%s], bättre lycka nästa gång!%n", bookName, o.getRandChapter(), c.getRandVers());
            }
        }
        else {
            System.out.printf("[FEL BOK] Osis, rätt svar [%s %s:%s], bättre lycka nästa gång!%n", bookName, o.getRandChapter(), c.getRandVers());
        }
    }
}


