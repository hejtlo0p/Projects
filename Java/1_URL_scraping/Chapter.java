import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.io.IOException;
import java.util.Random;
import java.util.Vector;

public class Chapter {
    private String url;
    private final Vector<String> chapter = new Vector<String>();
    private final int verses;
    private int randVers;

    Chapter(String bookName) {
        try {
            this.url = bookName;
            Document doc = Jsoup.connect(url).get();
            Elements verses = doc.getElementsByClass("verse");
            for (Element verse : verses) {
                verse.getElementsByClass("marker").remove(); // Remove footnotes.
                verse.getElementsByClass("verse-number").remove(); // Remove the verse number.
                this.chapter.add(verse.text());
            }
        }
        catch (IOException ex) {
            System.out.println(ex);
        }
        this.verses = chapter.size();
    }

    public String getUrl() {
        return url;
    }

    public Vector<String> getChapter() {
        return chapter;
    }

    public String generateRandomVerse() {
        Random ran = new Random();
        int num = ran.nextInt(verses);
        randVers = num + 1;
        //System.out.println("vers: " + randVers);
        return chapter.elementAt(num);
    }

    public int getVerses() {
        return verses;
    }

    public int getRandVers() {
        return randVers;
    }
}
