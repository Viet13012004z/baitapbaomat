
# BÀI TẬP MÔN: An toàn và bảo mật thông tin #
# Nguyễn Hoàng Việt
## BÀI TẬP 1: ##

### TÌM HIỂU CÁC PHƯƠNG PHÁP MÃ HOÁ CỔ ĐIỂN ###
1. Caesar
2. Affine
3. Hoán vị
4. Vigenère
5. Playfair

**Với mỗi phương pháp, hãy tìm hiểu:**
1. Tên gọi
2. Thuật toán mã hoá, thuật toán giải mã
3. Không gian khóa
4. Cách phá mã (mà không cần khoá)
5. Cài đặt thuật toán mã hoá và giải mã bằng code C++ và bằng html+css+javascript

# 1. Caesar

Mã hoá: C = (P + k) mod 26.

Giải mã: P = (C - k) mod 26.

Không gian khoá: 26 (thực 25).

Phá mã: brute-force thử 26 khoá hoặc phân tích tần suất.

# 2. Affine

Mã hoá: C = (aP + b) mod 26, với gcd(a,26)=1.

Giải mã: P = a⁻¹(C - b) mod 26.

Không gian khoá: 12 × 26 = 312.

Phá mã: brute-force 312 khoá hoặc dùng phân tích tần suất (monoalphabetic).

# 3. Hoán vị (Transposition)

Mã hoá: viết plaintext theo hàng, đọc theo cột dựa vào khoá (hoán vị cột).

Giải mã: điền ciphertext vào cột, đọc theo hàng.

Không gian khoá: n! (n = số cột).

Phá mã: thử n! hoán vị khi n nhỏ, dùng crib hoặc kiểm tra tính từ vựng.

# 4. Vigenère

Mã hoá: Ci = (Pi + Ki) mod 26, khoá lặp theo chuỗi.

Giải mã: Pi = (Ci - Ki) mod 26.

Không gian khoá: 26^L (L = độ dài khoá).

Phá mã: Kasiski, Friedman để tìm L, sau đó phân tích tần suất từng dãy (Caesar).

# 5. Playfair

Mã hoá: tạo bảng 5×5, mã hoá theo cặp chữ: cùng hàng → dịch phải, cùng cột → dịch xuống, khác hàng → đổi cột.

Giải mã: ngược lại (dịch trái, dịch lên).

Không gian khoá: tối đa 25!.

Phá mã: phân tích tần suất digraph, dùng heuristic (hill-climbing, simulated annealing) hoặc crib.

# Chạy chương trình mã hóa bằng Dev C++

1. Caesar

<img width="1486" height="731" alt="image" src="https://github.com/user-attachments/assets/f73d6755-317d-4b53-b794-fc6502e40a06" />

2. Affine

<img width="1481" height="724" alt="image" src="https://github.com/user-attachments/assets/32c37dd5-50af-4316-91f8-d9b9c7e1c8ce" />

3. Hoán vị 

<img width="1523" height="751" alt="image" src="https://github.com/user-attachments/assets/ebac9277-3f1a-40db-9396-87801f2872b7" />

4. Vigenere

<img width="1488" height="739" alt="image" src="https://github.com/user-attachments/assets/e240f4ee-96c4-430e-a024-bf8e4d9e44f5" />

5. Playfair

<img width="1473" height="757" alt="image" src="https://github.com/user-attachments/assets/800c1e78-2da8-4936-8ee7-d241f392778f" />

## Chạy chương trình bằng Vs

1. Caesar

<img width="1898" height="981" alt="image" src="https://github.com/user-attachments/assets/ad65294a-5773-4e5c-84e5-84edc978ccb5" />

2. Affine

<img width="1889" height="988" alt="image" src="https://github.com/user-attachments/assets/1e01eae9-32fc-46f0-ba07-c28609be5e8c" />

3. Hoán vị 

<img width="1866" height="991" alt="image" src="https://github.com/user-attachments/assets/963b71fd-7f19-496a-97b2-3b0fc600415d" />

4. Vigenere

<img width="1919" height="1003" alt="image" src="https://github.com/user-attachments/assets/f1ec444e-d78f-4d4d-b6fe-dfa5cd09fa1e" />

5. Playfair

<img width="1916" height="974" alt="image" src="https://github.com/user-attachments/assets/d46750f5-7487-4cd4-af02-3e6cd3789531" />
