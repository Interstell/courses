package home;

import java.io.FileWriter;
import java.util.Arrays;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.stage.Stage;

public class BubbleSortGraph extends Application {

	private static enum CASE {
		WORST, RANDOM, BEST
	};

	private final int startSize = 2_500;
	private final int finishSize = 25_000;
	private final int step = 2_500;
	private final int writingStep = 5_000;
	private static CASE currentCase = CASE.RANDOM;

	@Override
	public void start(Stage stage) {
		stage.setTitle("Bubble Sort: Classical vs Bidirectional");
		final NumberAxis xAxis = new NumberAxis();
		final NumberAxis yAxis = new NumberAxis();
		xAxis.setLabel("Elements sorted");
		yAxis.setLabel("Milliseconds");

		final LineChart<Number, Number> lineChart = new LineChart<Number, Number>(xAxis, yAxis);

		switch (currentCase) {
		case RANDOM:
			lineChart.setTitle("Bubble Sort: Classical vs Bidirectional (Random case)");
			break;
		case WORST:
			lineChart.setTitle("Bubble Sort: Classical vs Bidirectional (Worst case)");
			break;
		case BEST:
			lineChart.setTitle("Bubble Sort: Classical vs Bidirectional (Best case)");
			break;
		}

		XYChart.Series series1 = new XYChart.Series();
		XYChart.Series series2 = new XYChart.Series();
		series1.setName("BubbleSort");
		series2.setName("Bidirectional Bubble Sort");

		String bubbleFileName = null, shakerFileName = null;

		switch (currentCase) {
		case RANDOM:
			bubbleFileName = "BubbleClassicRandom.txt";
			shakerFileName = "BubbleBidirectionalRandom.txt";
			break;
		case WORST:
			bubbleFileName = "BubbleClassicWorst.txt";
			shakerFileName = "BubbleBidirectionalWorst.txt";
			break;
		case BEST:
			bubbleFileName = "BubbleClassicBest.txt";
			shakerFileName = "BubbleBidirectionalBest.txt";
			break;
		}

		FileWriter writerBubble = DataProcessor.openFile(bubbleFileName);
		FileWriter writerShaker = DataProcessor.openFile(shakerFileName);

		for (int i = startSize; i <= finishSize; i += step) {
			int ar[] = null;
			switch (currentCase) {
			case RANDOM:
				ar = DataProcessor.getRandomIntArray(i, true);
				break;
			case WORST:
				ar = DataProcessor.getRandomSortedIntArray(i, false, true);
				break;
			case BEST:
				ar = DataProcessor.getRandomSortedIntArray(i, true, true);
				break;
			}

			int arCopy[] = Arrays.copyOf(ar, ar.length);

			long tStart = System.nanoTime();
			BubbleSort.BubbleSort(ar);
			long tEnd = System.nanoTime();
			long delta = tEnd - tStart;
			double milliSeconds = delta / (double) 10e6;
			series1.getData().add(new XYChart.Data(i, milliSeconds));
			if (i % writingStep == 0) {
				DataProcessor.writeTimeToFile(writerBubble, i, milliSeconds);
			}
			System.out.format("%d %f vs ", i, milliSeconds);

			tStart = System.nanoTime();
			BubbleSort.BidirectionalBubbleSort(arCopy);
			tEnd = System.nanoTime();
			delta = tEnd - tStart;
			milliSeconds = delta / (double) 10e6;
			series2.getData().add(new XYChart.Data(i, milliSeconds));
			if (i % writingStep == 0) {
				DataProcessor.writeTimeToFile(writerShaker, i, milliSeconds);
			}
			System.out.format("%f\n", milliSeconds);
		}
		DataProcessor.closeWriter(writerBubble);
		DataProcessor.closeWriter(writerShaker);

		lineChart.setCreateSymbols(false);
		Scene scene = new Scene(lineChart, 800, 600);
		lineChart.getData().add(series1);
		lineChart.getData().add(series2);

		stage.setScene(scene);
		stage.show();
	}

	public static void main(String[] args) {
		launch(args);
	}
}
