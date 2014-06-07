
public class IteratorRunner {

	public static void main(String[] args) {
		Integer [] numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		ArrayIterator<Integer> iterator = new ArrayIterator<Integer>(numbers);

		while ( iterator.hasNext() ) {
			Integer item = iterator.next();
			System.out.println(item);
		}
	}
}