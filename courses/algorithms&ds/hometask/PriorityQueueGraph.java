package home;

import java.io.FileWriter;
import java.util.Arrays;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.stage.Stage;

public class PriorityQueueGraph extends Application {

	private final int startSize = 1000;
	private final int finishSize = 100000;
	private final int step = 1000;
	private final int writingStep = 10000;
	

	@Override
	public void start(Stage stage) {
		stage.setTitle("Deleting from PriorityQueue: Array vs Binary Heap");
		final NumberAxis xAxis = new NumberAxis();
		final NumberAxis yAxis = new NumberAxis();
		xAxis.setLabel("Elements in PriorityQueue");
		yAxis.setLabel("Milliseconds");

		final LineChart<Number, Number> lineChart = new LineChart<Number, Number>(xAxis, yAxis);
		lineChart.setTitle("Deleting from PriorityQueue: Array vs Binary Heap");

		XYChart.Series series1 = new XYChart.Series();
		XYChart.Series series2 = new XYChart.Series();
		series1.setName("Array realization");
		series2.setName("Binary Heap realization");

		FileWriter writerArray = DataProcessor.openFile("QueueArray.txt");
		FileWriter writerHeap = DataProcessor.openFile("QueueHeap.txt");

		for (int i = startSize; i <= finishSize; i += step) {
			int ar[] = DataProcessor.getRandomIntArray(i, true);
			int arCopy[] = Arrays.copyOf(ar, ar.length);

			PriorityQueueArray queueArray = new PriorityQueueArray(ar);
			PriorityQueueBinaryHeap queueHeap = new PriorityQueueBinaryHeap(arCopy);

			long tStart = System.nanoTime();
			queueArray.removeMax();
			long tEnd = System.nanoTime();
			long delta = tEnd - tStart;
			double milliSeconds = delta / (double) 10e6;
			series1.getData().add(new XYChart.Data(i, milliSeconds));
			if (i % writingStep == 0) {
				DataProcessor.writeTimeToFile(writerArray, i, milliSeconds);
			}
			System.out.format("%d %f vs ", i, milliSeconds);

			tStart = System.nanoTime();
			queueHeap.removeMax();
			tEnd = System.nanoTime();
			delta = tEnd - tStart;
			milliSeconds = delta / (double) 10e6;

			series2.getData().add(new XYChart.Data(i, milliSeconds));
			if (i % writingStep == 0) {
				DataProcessor.writeTimeToFile(writerHeap, i, milliSeconds);
			}
			System.out.format("%f\n", milliSeconds);
		}
		DataProcessor.closeWriter(writerArray);
		DataProcessor.closeWriter(writerHeap);
		lineChart.setCreateSymbols(false);
		Scene scene = new Scene(lineChart, 800, 600);
		lineChart.getData().add(series1); //show queueArray
		lineChart.getData().add(series2); //show queueHeap

		stage.setScene(scene);
		stage.show();
	}

	public static void main(String[] args) {
		launch(args);
	}
}