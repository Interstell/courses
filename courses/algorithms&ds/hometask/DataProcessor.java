package home;

import java.io.FileWriter;
import java.io.IOException;
import java.util.*;
import java.util.Random;

public class DataProcessor {

	final static Random rand = new Random();

	private static enum ORDER {
		RANDOM, ASCENDING, DESCENDING
	}

	private static int[] cacheRandom = null;
	private static int[] cacheAsc = null;
	private static int[] cacheDesc = null;
	private static final int cacheSize = 5010000; 

	public static int[] getRandomIntArray(int length, boolean cached) {
		if (cached)
			return getArrayFromCache(length, ORDER.RANDOM);
		int[] array = new int[length];
		for (int i = 0; i < array.length; i++) {
			array[i] = rand.nextInt();
		}
		return array;
	}

	public static int[] getRandomSortedIntArray(int length, boolean ascending, boolean cached) {
		if (cached)
			return getArrayFromCache(length, (ascending) ? ORDER.ASCENDING : ORDER.DESCENDING);
		Integer[] intArray = new Integer[length];
		for (int i = 0; i < length; i++) {
			intArray[i] = rand.nextInt();
		}
		if (ascending) {
			Arrays.sort(intArray);
		} else
			Arrays.sort(intArray, Collections.reverseOrder());
		int[] resArray = new int[length];
		for (int i = 0; i < length; i++) {
			resArray[i] = Integer.valueOf(intArray[i]);
		}
		return resArray;
	}

	private static int[] getArrayFromCache(int length, ORDER order) {
		switch (order) {
		case RANDOM:
			if (cacheRandom == null) {
				cacheRandom = getRandomIntArray(cacheSize, false);
			}
			return Arrays.copyOfRange(cacheRandom, 0, length);
		case ASCENDING:
			if (cacheAsc == null) {
				cacheAsc = getRandomSortedIntArray(cacheSize, true, false);
			}
			return Arrays.copyOfRange(cacheAsc, 0, length);
		case DESCENDING:
			if (cacheDesc == null) {
				cacheDesc = getRandomSortedIntArray(cacheSize, false, false);
			}
			return Arrays.copyOfRange(cacheDesc, 0, length);
		}
		return null;
	}

	public static FileWriter openFile(String fileName) {
		FileWriter writer = null;
		try {
			writer = new FileWriter(fileName, false);
		} catch (IOException ex) {
			System.out.println(ex.getMessage());
		}
		return writer;
	}

	public static void writeTimeToFile(FileWriter writer, int size, double time) {
		try {
			writer.write(Integer.toString(size) + " " + Double.toString(time) + "\n");
			writer.flush();
		} catch (IOException ex) {
			System.out.println(ex.getMessage());
		}

	}

	public static void closeWriter(FileWriter writer) {
		try {
			writer.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
