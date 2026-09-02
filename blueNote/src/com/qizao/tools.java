package com.qizao;

import java.util.Scanner;

public class tools {
    public  static int  safeInput() {
        Scanner sc = new Scanner(System.in);
        try {

            return  Integer.parseInt(sc.nextLine());
        }catch (Exception e){
            return  -1;
        }
    }
    //互动分计算
    public  static int calculateScore(int likes,int saves) {
        return  likes*2+saves*3;
    }
}
