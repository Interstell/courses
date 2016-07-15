package home;

import java.io.FileWriter;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.stage.Stage;

public class MergeGraph extends Application {

	private final int startSize = 10000;
	private final int finishSize = 1000000;
	private final int step = 10000;
	private final int writingStep = 100000;
	private final int timesToRepeat = 4;

	@Override
	public void start(Stage stage) {
		stage.setTitle("TwoWayMerge");
		final NumberAxis xAxis = new NumberAxis();
		final NumberAxis yAxis = new NumberAxis();
		xAxis.setLabel("Elements merged");
		yAxis.setLabel("Milliseconds");

		final LineChart<Number, Number> lineChart = new LineChart<Number, Number>(xAxis, yAxis);
		lineChart.setTitle("TwoWayMerge");

		XYChart.Series series = new XYChart.Series();
		series.setName("TwoWayMerge");

		FileWriter writerMerge = DataProcessor.openFile("TwoWayMerge.txt");

		for (int i = startSize; i <= finishSize; i += step) {
			int b[] = DataProcessor.getRandomSortedIntArray(i / 2, true, true);
			int c[] = DataProcessor.getRandomSortedIntArray(i / 2, true, true);

			double timeSum = 0;
			for (int j = 0; j < timesToRepeat; j++) {
				int a[] = new int[i];
				long tStart = System.nanoTime();
				Merge.TwoWayMerge(b, c, a);
				long tEnd = System.nanoTime();
				long delta = tEnd - tStart;
				timeSum += delta / (double) 10e6;
			}
			double milliSeconds = timeSum / timesToRepeat;
			series.getData().add(new XYChart.Data(i, milliSeconds));
			if (i % writingStep == 0) {
				DataProcessor.writeTimeToFile(writerMerge, i, milliSeconds);
			}
			System.out.format("%d %f\n", i, milliSeconds);
		}
		DataProcessor.closeWriter(writerMerge);
		lineChart.setCreateSymbols(false);

		Scene scene = new Scene(lineChart, 800, 600);
		lineChart.getData().add(series);

		stage.setScene(scene);
		stage.show();
	}

	public static void main(String[] args) {
		launch(args);
	}

}