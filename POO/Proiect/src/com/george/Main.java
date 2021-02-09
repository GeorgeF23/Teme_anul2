package com.george;

import com.george.tests.*;

import java.io.*;
import java.util.Scanner;

/**
 * Clasa principla ce contine punctul de intrare in program
 */
public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        ITest[] tests = {new Test1(), new Test2(), new Test3(), new Test4(), new Test5(), new Test6(), new Test7(), new Test8(), new Test9(), new Test10()};

        int testNumber = scanner.nextInt(); // Citesc numarul testului pe care vreau sa il rulez

        File outputFile = new File(String.format("tests/output/test%d/output.txt", testNumber));
        try {
            PrintStream outputStream = new PrintStream(new FileOutputStream(outputFile));
            // Fortez ca output-ul programului sa se faca in fisierul deschis mai sus
            System.setOut(outputStream);
            System.setErr(outputStream);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        tests[testNumber - 1].run();    // Execut testul
    }
}
