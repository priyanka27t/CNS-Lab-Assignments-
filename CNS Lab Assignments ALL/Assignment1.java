//CNS assignment 1
// implement caesar cipher

import java.util.Scanner;

public class Assi1{
    public static void main(String[] args){
        char[] arr = new char[26];
        int i;
        char j='a';
        for(i=0;i<26;i++){
                arr[i] = j;
                j++;
        }
        System.out.println(arr[1]);
        System.out.println(arr[2]);
        System.out.println(arr[25]);

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the text to encrypt: ");
        String input = sc.nextLine().toLowerCase();

        System.out.print("Enter the key: ");
        int key = sc.nextInt();


        String cipher= "";

        for(i=0;i<input.length();i++){
            char ch = input.charAt(i);
            if(ch >= 'a' && ch <= 'z'){
                int ot = ch - 'a';
                int newIndex = (ot + key) %26 ;
                cipher += arr[newIndex];
            }
            else{
                cipher += ch;
            }
        }

        System.out.println("Encrypted text: " + cipher);

        sc.close();

        String plaintext= "";

        for(i=0;i<cipher.length();i++){
            char ch = cipher.charAt(i);
            if(ch >= 'a' && ch <= 'z'){
                int ot = ch - 'a';
                int newIndex = (ot - key) %26 ;
                plaintext += arr[newIndex];
            }
            else{
                plaintext += ch;
            }
        }

        System.out.println("Decrypted text: " + plaintext);
    }
}


