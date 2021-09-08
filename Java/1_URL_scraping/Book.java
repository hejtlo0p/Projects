import javax.print.CancelablePrintJob;
import java.util.Random;
import java.util.Vector;

public class Book {
    private final Vector<String> urls;
    private final Vector<Chapter> book = new Vector<Chapter>();
    private final int chapters;
    private int randChapter;

    Book() {
        this.chapters = 22;
        this.urls = getUrlsFromBookName("1 Nephi");
        setChapter(13);
    }

    Book(String bookName, int chapters) {
        this.chapters = chapters;
        this.urls = getUrlsFromBookName(bookName);
        generateRandomChapter();
        setChapter(randChapter-1);
    }

    private Vector<String> getUrlsFromBookName(String bookName) {
        Vector<String> temp = new Vector<String>();
        int chapters = 1;
        switch (bookName) {
            case "1 Nephi":
                while (chapters <= this.chapters) {
                    String url = String.format("https://www.churchofjesuschrist.org/study/scriptures/bofm/1-ne/%s?lang=swe", chapters);
                    temp.add(url);
                    chapters++;
                }
                break;
            case "2 Nephi":
                while (chapters <= this.chapters) {
                    String url = String.format("https://www.churchofjesuschrist.org/study/scriptures/bofm/2-ne/%s?lang=swe", chapters);
                    temp.add(url);
                    chapters++;
                }
                break;
            case "Jakob":
                while (chapters <= this.chapters) {
                    String url = String.format("https://www.churchofjesuschrist.org/study/scriptures/bofm/jacob/%s?lang=swe", chapters);
                    temp.add(url);
                    chapters++;
                }

                break;
            case "Enos":
                while (chapters <= this.chapters) {
                    String url = String.format("https://www.churchofjesuschrist.org/study/scriptures/bofm/enos/%s?lang=swe", chapters);
                    temp.add(url);
                    chapters++;
                }
                break;
            case "Jarom":
                while (chapters <= this.chapters) {
                    String url = String.format("https://www.churchofjesuschrist.org/study/scriptures/bofm/jarom/%s?lang=swe", chapters);
                    temp.add(url);
                    chapters++;
                }
                break;
            case "Omni":
                while (chapters <= this.chapters) {
                    String url = String.format("https://www.churchofjesuschrist.org/study/scriptures/bofm/omni/%s?lang=swe", chapters);
                    temp.add(url);
                    chapters++;
                }
                break;
            case "Mormons ord":
                while (chapters <= this.chapters) {
                    String url = String.format("https://www.churchofjesuschrist.org/study/scriptures/bofm/w-of-m/%s?lang=swe", chapters);
                    temp.add(url);
                    chapters++;
                }
                break;
            case "Mosiah":
                while (chapters <= this.chapters) {
                    String url = String.format("https://www.churchofjesuschrist.org/study/scriptures/bofm/mosiah/%s?lang=swe", chapters);
                    temp.add(url);
                    chapters++;
                }
                break;
            case "Alma":
                while (chapters <= this.chapters) {
                    String url = String.format("https://www.churchofjesuschrist.org/study/scriptures/bofm/alma/%s?lang=swe", chapters);
                    temp.add(url);
                    chapters++;
                }
                break;
            case "Helaman":
                while (chapters <= this.chapters) {
                    String url = String.format("https://www.churchofjesuschrist.org/study/scriptures/bofm/hel/%s?lang=swe", chapters);
                    temp.add(url);
                    chapters++;
                }
                break;
            case "3 Nephi":
                while (chapters <= this.chapters) {
                    String url = String.format("https://www.churchofjesuschrist.org/study/scriptures/bofm/3-ne/%s?lang=swe", chapters);
                    temp.add(url);
                    chapters++;
                }
                break;
            case "4 Nephi":
                while (chapters <= this.chapters) {
                    String url = String.format("https://www.churchofjesuschrist.org/study/scriptures/bofm/4-ne/%s?lang=swe", chapters);
                    temp.add(url);
                    chapters++;
                }
                break;
            case "Mormon":
                while (chapters <= this.chapters) {
                    String url = String.format("https://www.churchofjesuschrist.org/study/scriptures/bofm/morm/%s?lang=swe", chapters);
                    temp.add(url);
                    chapters++;
                }
                break;
            case "Ether":
                while (chapters <= this.chapters) {
                    String url = String.format("https://www.churchofjesuschrist.org/study/scriptures/bofm/ether/%s?lang=swe", chapters);
                    temp.add(url);
                    chapters++;
                }
                break;
            case "Moroni":
                while (chapters <= this.chapters) {
                    String url = String.format("https://www.churchofjesuschrist.org/study/scriptures/bofm/moro/%s?lang=swe", chapters);
                    temp.add(url);
                    chapters++;
                }
                break;
            default:
                System.err.println("[" + bookName + "] is not an option!");
                break;
        }
        return temp;
    }

    public Vector<String> getUrls() {
        return urls;
    }

    public Vector<Chapter> getBook() {
        return book;
    }

    private void setChapter(int chapter) {
        Chapter c = new Chapter(this.urls.elementAt(chapter));
        book.add(c);
    }

    public void generateRandomChapter() {
        Random ran = new Random();
        int num = ran.nextInt(chapters);
        randChapter = num + 1;
        //System.out.println("chapter: " + randChapter);
    }

    public int getChapters() {
        return chapters;
    }

    public int getRandChapter() {
        return randChapter;
    }
}
