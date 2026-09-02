package com.qizao;

import java.util.Scanner;

public class q3_countLongReviews {
    public  static int[] mySplit(int reviewsN,String detail){
        //循环判断非数字截取
        int[] arr=new int[reviewsN];
        String temp ="";
        detail+=".";//保证最后一个数字弹出
        int n=0;//计数
        for (int i = 0; i < detail.length(); i++) {
            if(Character.isDigit(detail.charAt(i))){
                temp+=detail.charAt(i);
            }else {
                arr[n]=Integer.parseInt(temp);
                n++;
                temp="";
            }
        }
        return arr;
    }
    public static void main(String[] args) {
        int reviewsN =tools.safeInput();
        Scanner sc = new Scanner(System.in);
        String detail =  sc.nextLine();
        //字符串裁剪String[] manyReviews = detail.split(",");
        int[] result = mySplit(reviewsN,detail);
        int n=0;
        for(int i:result){
            if(i>=20){
                n++;
            }
        }
        System.out.println(n);



    }



}
