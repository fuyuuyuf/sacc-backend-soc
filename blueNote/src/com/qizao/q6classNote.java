package com.qizao;

import java.util.Scanner;

public class q6classNote {
    static class Note{//定义
        String title;
        int likes;
        public Note(String title,int likes){
            this.title=title;
            this.likes=likes;
        }
        public String getInfo() {
            return title+ "："+likes;
        }
        public void addLikes() {
            this.likes++;
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Note note1 = new Note(sc.nextLine(),Integer.parseInt(sc.nextLine()));
        int count = Integer.parseInt(sc.next());
        for (int i = 1; i <= count; i++) {
            note1.addLikes();
        }
        System.out.println( note1.getInfo());
        sc.close();
    }
}
