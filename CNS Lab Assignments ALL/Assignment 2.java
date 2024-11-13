import java.util.Scanner;

public class Assi2 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the text to encrypt: ");
        String input = sc.nextLine().toLowerCase();

        System.out.print("Enter the key: ");
        String key = sc.nextLine().toLowerCase();

        String newkey = extendKey(key, input.length());

        String cipher = encrypt(input, newkey);
        System.out.println("Encrypted text: " + cipher);

        String plaintext = decrypt(cipher, newkey);
        System.out.println("Decrypted text: " + plaintext);

        sc.close();
    }

    private static String extendKey(String key, int length) {
        while (key.length() < length) {
            key += key;
        }
        return key;
    }

    private static String encrypt(String input, String key) {
        StringBuilder cipher = new StringBuilder();
        for (int i = 0; i < input.length(); i++) {
            char ch = input.charAt(i);
            if (ch >= 'a' && ch <= 'z') {
                int inputIndex = ch - 'a';
                int keyIndex = key.charAt(i) - 'a';
                int newIndex = (inputIndex + keyIndex) % 26;
                cipher.append((char) (newIndex + 'a'));
            } else {
                cipher.append(ch);
            }
        }
        return cipher.toString();
    }

    private static String decrypt(String cipher, String key) {
        StringBuilder plaintext = new StringBuilder();
        for (int i = 0; i < cipher.length(); i++) {
            char ch = cipher.charAt(i);
            if (ch >= 'a' && ch <= 'z') {
                int cipherIndex = ch - 'a';
                int keyIndex = key.charAt(i) - 'a';
                int newIndex = (cipherIndex - keyIndex +26) % 26;
                plaintext.append((char)(newIndex + 'a'));
            } else {
                plaintext.append(ch);
            }
        }
        return plaintext.toString();
    }
}
