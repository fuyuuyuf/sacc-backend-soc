package com.qizao;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class q5bubble {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int[] result = new int[3];
        int n = tools.safeInput();//放下面会重复计算报错
        List<Integer> list = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            result= q3_countLongReviews.mySplit(3,sc.nextLine());
            //System.out.println(result[0]*2+result[1]*3+result[2]);//公式计算
            list.add(result[0]*2+result[1]*3+result[2]);
        }

        //冒泡排序
        int temp =0;
        for (int i = 0; i < list.size()-1; i++) {
            for (int j = i + 1; j < list.size(); j++) {
                if (list.get(i)<=list.get(j)) {
                    temp=list.get(i);
                    list.set(i,list.get(j));
                    list.set(j,temp);
                }
            }
        }
        for(int a:list){
            System.out.println(a);
        }

    }


}
