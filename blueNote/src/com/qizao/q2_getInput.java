package com.qizao;

import java.util.Scanner;

public class q2_getInput {
    public static void main(String[] args) {
        Scanner sc  = new Scanner(System.in);
        //获取输入
        //System.out.print("请分别输入一行字符串表示昵称\n一个整数 notes，表示已发布笔记数\n一个个字符串 tag，表示关注的话题");

        String name = sc.nextLine();
        int notes;
        //其他输入异常处理
        try {
            notes = Integer.parseInt( sc.nextLine());
        }catch (Exception e) {
            notes = -1;
        }

        String tag = sc.nextLine();
        System.out.println(String.format("%s has %d notes and follows %s.", name, notes, tag));
    }
}
