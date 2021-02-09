import com.george.products.Painting;
import com.george.products.PaintingBuilder;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assertions;


class TestPaintingBuilder {
    @Test
    void test1(){
        Painting painting = new PaintingBuilder()
                .withId(0)
                .withName("Monalisa")
                .withMinimumPrice(1000.0)
                .withYear(2020)
                .withAuthorName("Picasso")
                .withColors("ULEI")
                .build();
        Assertions.assertNotNull(painting);
    }

    @Test
    void test2(){
        Painting painting = new PaintingBuilder()
                .withId(0)
                .withYear(2020)
                .withColors("ULE2I")
                .build();
        Assertions.assertNull(painting);
    }
}
