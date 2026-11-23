1. Thuật toán và lý do lựa chọn trong thực tế
- Insertion Sort (Live Auction Monitor): Insertion Sort hoạt động hiệu quả với dữ liệu gần như đã được sắp xếp, có độ phức tạp tốt nhất là O(N). Thuật toán phù hợp để xử lý các giá đấu mới khi chúng chỉ tạo ra những thay đổi nhỏ trong thứ tự dữ liệu hiện tại.
- Selection Sort (Top-K Bid Finder): Selection Sort có thể tìm ra các giá đấu lớn nhất chỉ sau một vài vòng lặp đầu tiên mà không cần sử dụng thêm vector. Điều này phù hợp với chức năng tìm Top-K giá đấu trong các tập dữ liệu nhỏ.
- Interchange Sort (Price Anomaly Validator): Interchange Sort có cách cài đặt đơn giản và thuận tiện cho việc đếm số lần hoán đổi phần tử (swap). Thuật toán có thể được sử dụng để kiểm thử và xác thực các lô dữ liệu đấu giá có kích thước nhỏ.
- Bubble Sort Early Stop (Stabilization Detector): Điều kiện dừng sớm cho phép thuật toán kết thúc ngay khi không có phép hoán đổi nào xảy ra trong một lượt duyệt hoàn chỉnh. Nhờ đó, thuật toán có thể nhanh chóng xác định dữ liệu đã được sắp xếp hay chưa.
- Quick Sort (Full Historical Sorter): Quick Sort có độ phức tạp trung bình O(N log N), phù hợp để sắp xếp các tập dữ liệu lịch sử đấu giá có kích thước lớn. Chiến lược chọn chốt Median-of-Three giúp giảm khả năng tạo ra các phân hoạch mất cân bằng.

2. Thời gian thực thi Quick Sort trên 100.000 bản ghi
Thời gian thực thi đo được khi sắp xếp 100.000 bản ghi là 121 ms.

3. Lỗi gặp phải và cách xử lý
Lỗi: Chương trình thông báo không tìm thấy tệp khi thực hiện tạo dữ liệu kiểm thử gồm 100.000 bản ghi.
Chẩn đoán và xử lý: Đối tượng ofstream có thể tạo tệp nhưng không tự động tạo thư mục chứa tệp đó. Vì vậy, em đã sử dụng lệnh mkdir test_data trong Terminal để tạo thư mục trước. Sau đó, chương trình đã có thể tạo tệp large.txt thành công.

4. Các câu lệnh đã sử dụng với LLM
[Green] "Hãy tạo 5 bộ dữ liệu đầu vào thuộc các trường hợp biên (edge-case) cần cân nhắc khi kiểm thử thuật toán."
[Green] "Giải thích tại sao hàm quickSortWrapper lại cần thiết."
[Yellow] "Lỗi không tương thích kiểu dữ liệu (type mismatch) khi sử dụng std::min là gì và cần sửa các kiểu dữ liệu như thế nào cho đúng?"

5. Độ phức tạp trong trường hợp xấu nhất của Quick Sort sử dụng Median-of-Three
Độ phức tạp trong trường hợp xấu nhất của thuật toán vẫn là O(N²). Mặc dù Median-of-Three lựa chọn phần tử trung vị trong ba vị trí đầu, giữa và cuối làm chốt (pivot), phương pháp này không đảm bảo mọi lần phân hoạch đều cân bằng. Đặc biệt, với những tập dữ liệu có nhiều phần tử trùng khóa so sánh, thuật toán vẫn có thể tạo ra các phân hoạch mất cân bằng, dẫn đến số lần gọi đệ quy tăng lên đáng kể.
