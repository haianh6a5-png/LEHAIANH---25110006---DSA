1. Thuật toán và lý do lựa chọn trong thực tế
- Insertion Sort (Live Auction Monitor): Khi luồng dữ liệu đấu giá gần như đã được sắp xếp, mỗi giá đấu mới chèn vào chỉ cần dịch chuyển O(1) vị trí để về đúng thứ tự, giúp tổng chi phí thực thi tiến về mức tuyến tính O(N) thay vì O(N ^ 2)
- Selection Sort (Top-K Bid Finder): Selection Sort có thể tìm ra K giá đấu cao nhất chỉ sau K vòng lặp đầu tiên mà không cần cấp phát thêm bộ nhớ phụ (in-place). Điều này tối ưu cho tác vụ truy xuất Top-K trên các tập dữ liệu nhỏ
- Interchange Sort : Với các lô dữ liệu kiểm thử kích thước nhỏ (N <= 50), số phép so sánh tối đa chỉ vào khoảng (50 × 49) / 2 = 1.225 phép tính - mức chi phí O(N ^ 2) hoàn toàn không đáng kể về mặt thời gian thực thi, đổi lại mã nguồn ngắn gọn, dễ kiểm chứng và thuận tiện để đếm trực tiếp số lần hoán đổi (swapCount)
- Bubble Sort Early Stop (Stabilization Detector): Cờ kiểm tra hoán đổi (swapped) cho phép thuật toán dừng ngay sau lượt duyệt đầu tiên nếu không có cặp phần tử nào sai thứ tự, giúp xác định nhanh trạng thái ổn định của dữ liệu với độ phức tạp O(N)
- Quick Sort (Full Historical Sorter): Quick Sort đạt độ phức tạp trung bình O(N log N) và tận dụng tốt bộ nhớ đệm (cache locality), đáp ứng yêu cầu xử lý các tập dữ liệu lịch sử đấu giá quy mô lớn. Chiến lược chọn chốt Median-of-Three giúp hạn chế tình trạng phân hoạch lệch trên dữ liệu đã sắp xếp sẵn hoặc đảo ngược

2. Thời gian thực thi Quick Sort trên 100.000 bản ghi
Thời gian thực thi đo được khi sắp xếp 100.000 bản ghi là 46ms

3. Lỗi gặp phải và cách xử lý
Lỗi: Khi chạy chương trình để sinh 100.000 bản ghi vào đường dẫn test_data/large.txt, màn hình hiển thị thông báo "Error: Cannot create file" do luồng ghi tệp mở thất bại
Chẩn đoán và xử lý: Đối tượng std::ofstream chỉ có khả năng tạo tệp mới bên trong một thư mục đã tồn tại chứ không tự động khởi tạo thư mục cha. Để khắc phục, em đã chạy lệnh mkdir test_data trong Terminal (sau đó bổ sung std::filesystem::create_directories vào mã nguồn) để đảm bảo thư mục đích luôn tồn tại trước khi ghi tệp

4. Các câu lệnh đã sử dụng với LLM
- [Green] "Hãy tạo 5 bộ dữ liệu đầu vào thuộc các trường hợp biên (edge-case) cần cân nhắc khi kiểm thử thuật toán."
- [Green] "Giải thích tại sao hàm quickSortWrapper lại cần thiết."
- [Yellow] "Lỗi không tương thích kiểu dữ liệu (type mismatch) khi sử dụng std::min là gì và cần sửa các kiểu dữ liệu như thế nào cho đúng?"

5. Độ phức tạp trong trường hợp xấu nhất của Quick Sort sử dụng Median-of-Three
Độ phức tạp trong trường hợp xấu nhất của thuật toán vẫn là O(N ^ 2). Dù Median-of-Three chọn trung vị của 3 phần tử đầu, giữa và cuối làm chốt (pivot) để tránh trường hợp dữ liệu đã sắp xếp, phương pháp này không đảm bảo mọi bước phân hoạch đều cân bằng. Về mặt lý thuyết, vẫn tồn tại các bộ dữ liệu đối kháng ("median-of-three killer") được sắp đặt sao cho giá trị trung vị được chọn luôn rơi sát vào phần tử nhỏ nhất hoặc lớn nhất của mảng con, khiến phân hoạch bị lệch hoàn toàn ở mọi bước đệ quy và đẩy chi phí lên O(N ^ 2)
