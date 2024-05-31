# Employee Sponsor - Final Lab <br>

## Lí do có bài tập này

Em là Lưu Thái Toàn, học lớp OOP lý thuyết 22_4 của thầy và học thực hành của lớp thầy Thái. Tuy thầy Thái có cho làm bài tập của thầy nhưng mà hàm main là do thầy Thái cho, nên em thấy hơi bị giới hạn trong việc thiết kế và không thể tự thiết kế theo bản thân.

Ngoài ra, em thấy thầy chấm bài thi giữa kì của các bạn rất kĩ. Nên em cũng muốn được thầy chấm xem em còn sai sót gì không hay những thứ em thiết kế có gặp vấn đề gì trong quá trình mở rộng. Nếu không có sai sót thì em cũng muốn nhận được ba chữ "Bài làm tốt" của thầy =))).

Thêm một lí do bên lề nữa, là em đang bắt đầu học C# ASP.NET cho backend, và em nghe thầy nói thầy có dạy Lập trình Windows. Em muốn hỏi thầy có gợi ý sách(website) cho hướng đi này để em về nghiên cứu. Em có khả năng đọc được sách tiếng anh, sách giảng dạy hoặc cả document thô ráp. Cảm ơn thầy rất nhiều ạ.

## Đôi nét về bài làm

Bài làm có cài đặt `Doxygen`, đường dẫn là: `./Project1/docs/html/index.html`. Để dễ nhận xét thầy có thể vào xem `Class Hierachy` để xem thiết kế của em. Tuy nhiên... em chưa document code... vì em hơi hơi hơi lười viết tiếng anh. Em sẽ giải thích rõ các `Class` em tự thiết kế trong file này. Và để thầy không cần phải mở code lên đọc, em sẽ để một số phần code mà em nghĩ là quan trọng ở trong file này và giải thích về nó.

Tuy là bài làm dựa trên Final Lab của thầy nhưng thay vì chỉ một loại `Proposal` (`Tour`/`Book`), em xây dựng các `Class` dựa trên việc có thể sử dụng với bất kì `Proposal` nào và tuân theo `O` trong `SOLID` (có thể mở rộng ra nhiều `Class` khác ngoài `Proposal`).

## Version 1

Đây là Version ban đầu của bài làm. Dựa trên một loại `Proposal` duy nhất (`Tour`).

```cpp
void version1() {
    Factory<IParsable*>::getInstance()->registerWith("Employee", new EmployeeParser());
    Factory<IParsable*>::getInstance()->registerWith("Tour", new TourParser());
	string filename = "TourProposal.txt";
	TourProposalTextDataProvider provider(filename);
	vector<TourProposal> proposals = provider.getProposals();

	vector<string> headers = { "STT", "Name", "Classifcation", "Destination", "Price", "Support", "Amount" };
	vector<int> columnSizes = { 3, 15, 14, 20, 14, 9, 12 };
	TourProposalToTableConverter converter(headers, columnSizes);

	cout << "Version 1 of Employee Sponsor Counting:" << endl;
	cout << "Found " << proposals.size() << " proposals buy travel Tour." << endl;
	cout << converter.convert(proposals) << endl;

	double total = 0.0f;
	for (auto proposal : proposals) {
		total += proposal->getTotalAmount();
	}
	cout << "Total amount of all proposals: " << total << endl;
}
```

Trong phiên bản này, đa số các `Class` đều riêng biệt, ít sự liên kết với nhau. Chủ yếu là được xây dựng dựa trên các `Class` thầy đã định nghĩa sẵn trong các Lab trước.

Tuy đoạn code hoạt động đúng theo yêu cầu nhưng là một thiết kế tệ vì thiếu khả năng mở rộng, các hàm cố định và phải chỉnh sửa ở nhiều nơi.

Các vấn đề có thể kể đến như:

-   Chính sách của công ty là cố định. Nếu muốn thay đổi chính sách, sẽ phải vô các `Class` `Employee`, `TourProposal` để sửa.

-   Việc tính toán phần trăm tài trợ không phải nghiệp vụ của 2 `Class` kể trên.

-   Khi công ty muốn thêm một loại `Proposal` thì phải sửa lại gần như tất cả nghiệp vụ.

## Version 2

Đây là Version được tạo nên dựa trên 2 yêu cầu: `Future Policy Changes` và `Multiple Proposal`.

### Hàm main:

```cpp
void config() {
    Policy* policy = Policy::getInstance();
	policy->registerWith({ 0, 2 }, "Fresher", 35);
	policy->registerWith({ 2, 3 }, "Junior", 45);
	policy->registerWith({ 3, 4 }, "Middle", 60);
	policy->registerWith({ 4, 20 }, "Senior", 75);

    Factory<IParsable*>* factory= Factory<IParsable*>::getInstance();
	factory->registerWith("Employee", new EmployeeParser());
	factory->registerWith("Tour", new TourParser());
	factory->registerWith("Book", new BookParser());

	// This seems to be over-engineered, i dont know any alternatives way to do this...
    ProposalFactory* proposalFac = ProposalFactory::getInstance()
	proposalFac->registerWith("Tour", [](Employee* employee, Object* tour) {
		return new TourProposal(employee, dynamic_cast<Tour*>(tour));
		});
	proposalFac->registerWith("Book", [](Employee* employee, Object* book) {
		return new BookProposal(employee, dynamic_cast<Book*>(book));
		});
}

void version2() {
	config2();
	string filename = "MixedProposal.txt";
	ProposalTextDataProvider provider(filename);
	vector<IProposal*> proposals = provider2.getProposals();

	vector<string> headers = { "STT", "Name", "Classifcation",
                                "OfferName", "Price", "Support", "Amount" };
	vector<int> columnSizes = { 3, 20, 14, 20, 15, 10, 13 };
	ProposalToTableConverter converter(headers, columnSizes);

	cout << "Version 2 of Employee Sponsor Counting:" << endl;
	cout << "Found " << proposals2.size() << " proposals." << endl;
	cout << converter2.convert(proposals) << endl;

	double total = 0.0f;
	for (auto proposal : proposals) {
		total += proposal->getTotalAmount();
		delete proposal;
	}
	cout << "Total amount of all proposals: " << total << endl;
}

```

### Xử lý Future Policy Changes

Tạo `Class Policy` đảm nhiệm việc xử lý các chính sách của công ty. `Policy` sẽ chứa các `PolicyItem` là nội dung của các chính sách, và có 2 hàm chính: `registerWith()` và các hàm `getter()` để lấy dữ liệu dựa trên `yearsOfWork`.

Ngoài ra, mỗi công ty chỉ có 1 chính sách thuộc dạng `Kinh nghiệm - Trình độ - Phần trăm`. Vì vậy, chỉ nên tồn tại 1 `Instance Policy` duy nhất trong chương trình --> Sử dụng `Singleton Pattern` cho `Policy`.

```cpp
class PolicyItem :public Object {
private:
	pair<int, int> _rangeYearsOfWork;
	string _classification;
	int _percentOfSponsoring;
};


class Policy : public Object {
private:
	vector<PolicyItem> _policyItems;
    inline static Policy* _instance = nullptr;

private:
	Policy();

public:
	static Policy* getInstance();
	void registerWith(pair<int, int> yearsOfWork, string classification, int percentOfSponsoring);
    int getPercentOfSponsorship(double yearsOfWork);
	string getClassification(double yearsOfWork);
}
```

### Xử lý việc định nghĩa Multiple Proposal

Thay vì để `TourProposal` tồn tại độc lập, cho `Class` này kế thừa `Interface IProposal`. Khi cần thêm các `Proposal` mới cũng sẽ kế thừa `Interface` này.

```cpp
class IProposal : public Object {
public:
	virtual Employee* getEmployee() = 0;
	virtual Object* getSponsoredLocation() = 0;
	virtual Double getTotalAmount() = 0;
};
```

### Xử lý việc tạo Multiple Proposal

Tạo thêm một `ProposalFactory` chịu trách nhiệm tạo các `Proposal Instance` dựa trên tên của loại tài trợ (`Tour`, `Book`). Lưu ý rằng `Class` này vẫn được cài đặt bằng `Singleton`.

Có 2 lí do cho việc phải tạo `Class` này:

-   Một là tương tự như với `Factory<IParsable*>`, cần một thứ có thể tạo `Instance` một cách dynamic dựa trên một chuỗi.

-   Hai là tuy tồn tại `Factory<IProposal*>`, nhưng nó không hoạt động theo cách chúng ta cần. Việc khởi tạo `IProposal*` phải dựa trên 2 `Class` `Employee` và `SponsoredLocation`. Nhưng hàm `create()` của `Factory<IProposal*>` không có tham số truyền vào. Nên ta cần phải tạo một `Factory` mới có duy nhất 1 nghiệp vụ là tạo `Proposal`.

Ban đầu, `ProposalFactory` được định nghĩa như sau:

```cpp
class ProposalFactory : public Object {
private:
    map<string, IProposal*> _proposals;

public:
	IProposal* create(string type, Employee* employee, Object* sponsoredLocation) {
		IProposal* proposal = _proposals[type];
		proposal->setEmployee(employee);
		proposal->setSponsored(sponsoredLocation);
		return proposal;
	}

    IProposal* registerWith(string type, IProposal* proposal) {
		_proposals.insert({ name, proposal });
    }
};

// Call this in main
ProposalFactory::getInstance()->registerWith("Tour", new TourProposal());
```

Đoạn code này hoạt động tốt, không xảy ra vấn đề. Nhưng theo mặt cá nhân thì em không thích việc sử dụng `setter()` ngay bên dưới hàm tạo. Và việc định nghĩa các hàm `setter()` cho tất cả các `Proposal` chỉ cho mục đích tạo `Instance` không phải là một thiết kế tốt. Xét về tính nghiệp vụ, `một lời nói ra ngựa giỏi đuổi không kịp`, nên nếu một lời đề nghị mà có thể thay đổi bất thường thì vô lý. Nên em đã xem xét về các phương án khác. Và việc sử dụng `lambda` là giải pháp duy nhất mà em nghĩ ra và thực hiện được.

```cpp
class ProposalFactory : public Object {
private:
	map<string, function<IProposal* (Employee*, Object*)>> _proposals;

public:
	IProposal* create(string type, Employee* employee, Object* sponsoredLocation) {
		IProposal* proposal = _proposals[type](employee, sponsoredLocation);
		return proposal;
	}

    IProposal* registerWith(string type, function<IProposal*(Employee*, Object*)> proposalCreatingFunc) {
		_proposals.insert({ name, proposalCreatingFunc });
    }
};

// Call this in main
ProposalFactory::getInstance()->registerWith("Tour", [](Employee* employee, Object* tour) {
		return new TourProposal(employee, dynamic_cast<Tour*>(tour));
	});
```

Em cảm thấy giải pháp này vẫn chưa đủ tốt, nhưng em đã thử tìm hiểu về các `Creational Pattern` khác mà vẫn không nghĩ ra. Em mong là thầy có phương án giải quyết tốt hơn cho vấn đề này.

### Tổng kết

Phiên bản này có thể coi là hoàn thiện về vấn đề nghiệp vụ và khả năng mở rộng của chương trình. Nhưng vẫn còn vài vấn đề có thể tiếp tục nâng cấp:

-   Tạo một `Class TableConverter` để `ProposalConverter` kế thừa, và `Class` này có khả năng được kế thừa để tạo nhiều loại bảng.

-   Xây dựng `Class DoubleToCurrencyConverter` để đa dạng hóa cách in tiền tệ.

-   Xây dựng `Class ProposalManager` để quản lý mảng `Proposal`.

## Version 3

Đây là Version hiện tại của chương trình.

```cpp
void version3(){
    config2();
	string filename = "MixedProposal.txt";
	ProposalTextDataProvider provider(filename);
	ProposalManager manager(provider.getProposals());

	std::vector<string> headers = { "STT", "Name", "Classifcation", "OfferName", "Price", "Support", "Amount" };
	std::vector<int> columnSizes = { 3, 20, 14, 20, 15, 10, 13 };
	TableFormat tableConfig3(headers, columnSizes, "|");
	ProposalToTableConverter converter(tableConfig3);

	std::cout << "Version 3 of Employee Sponsor Counting:" << std::endl;
	std::cout << "Found " << manager.size() << " proposals." << std::endl;
	std::cout << converter.convert(manager.getProposals()) << std::endl;

	DoubleToCurrencyConverter currencyConverter(CurrencyFormat(",", "$", 0));
	Double totalFunds = manager.calculateTotalFunds();
	std::cout << "Total amount of all proposals: " << currencyConverter.convert(dynamic_cast<Object*>(&totalFunds));
}
```

### Về `DoubleToCurrencyConverter`

Được xây dựng tương tự `Class IntegerToCurrencyConverter` trong Lab08 của thầy.

### Về `ProposalManager`

Được xây dựng để đưa nghiệp vụ tính toán Tổng tiền tài trợ từ hàm Main về đúng đối tượng.

### Về ý tưởng của `TableConverter`

Thực hiện dựa trên ý tưởng xây dựng bảng một cách tự động và áp dụng được cho nhiều kiểu dữ liệu khác nhau. Ví dụ ta đang có bảng của đề bài như sau:

```cpp
	std::vector<string> headers = { "STT", "Name", "Classifcation", "OfferName", "Price", "Support", "Amount" };
	std::vector<int> columnSizes = { 3, 20, 14, 20, 15, 10, 13 };
```

Nếu ta muốn thêm cột `Email` của nhân viên, chúng ta thêm như thế nào? Trong trường hợp bình thường, sử dụng `std::format` hoặc `std::istringstream`, ta sẽ phải vào trong đoạn code `convert()` để sửa. Hoặc một nghiệp vụ dễ dàng hơn nhiều, đó là thu nhỏ cột `Amount` xuống còn 12 ô, ta cũng vẫn phải vào sửa trực tiếp `convert()`. Việc này rất bất tiện.

Để xử lý việc này, ta sẽ cố gắng biến hàm `convert()` có thể tự động thực hiện việc này chỉ dựa vào `headers` và `columnSizes` truyền vào. Nghĩa là thay vì gán giá trị `5` cố định vào bên trong `std::format("{:>5}")`, ta sẽ gán 1 biến `x` vào `std::format("{:>x}")`.

Tuy `std::format` không cho phép làm điều đó, nhưng một hàm trong cùng thư viện `<format>` có thể. Đó là `std::vformat()`.

Ta có thể làm được một việc như sau:

```cpp
    std::string formattedString = "He{}, World!";
    std::cout << std::vformat(formattedString, std::make_format_args("llo")); // Output: Hello, World!
```

Có thể thấy việc định nghĩa một chuỗi như trên là không thể với `std::format()` nhưng hoàn toàn có thể với `std::vformat()`. Điều này chứng minh ý tưởng xây dựng bảng tự động hoàn toàn có thể thực thi được.

Cụ thể sẽ thực hiện tương tự như sau:

```cpp
    int precision = 0;
    cin >> precision; // Example: input 2 -> precision = 2

    string formattedString = std::format("{{:.{}f}}", precision); // "{{" in format is considered as "{"
    string result = std::vformat(formattedString, std::make_format_args(12.345678)); // formattedString = "{:.2f}"

    std::cout << result; // Output: 12.34
```

Việc sử dụng `std::vformat()` sẽ dễ dàng xử lý được việc xây dựng tự động bảng. Ngoài ra, `std::vformat()` sẽ phải đi kèm với `std::make_format_args()`.

### Về cách cài đặt của `TableConverter`

Để `TableConverter` là một `Class` chung cho nhiều dữ liệu và có thể truyền tham số bất kì vào hàm `convert()` thì `Template` là lựa chọn tối ưu nhất.

```cpp

template <class T>
class TableConverter : public Object {
protected:
	TableFormat _config;

protected:
	TableConverter();
	TableConverter(TableFormat config);
	std::tuple<std::string, std::vector<std::string>> prepareTableStructure();

public:
	std::string convert(std::vector<T> data);

protected:
	class RowConverter : public Object {
	protected:
		std::vector<std::string> _columnFormats;
		int _index = 1;
		std::vector<int> _columnSizes;
		std::vector<std::string> _rowData;

	public:
		virtual std::vector<std::string> setRowData(T data) { return {}; };

		RowConverter(std::vector<std::string> columnFormats, std::vector<int> columnSizes) {
			this->_columnFormats = columnFormats;
			this->_columnSizes = columnSizes;
		}
		std::string convert(T data);
	};
};

// Implementation Snippet

```

Ngay bên dưới sẽ cài đặt tất cả các hàm trong `Class` này trừ hàm `RowConverter::setRowData()` (sẽ nhắc lại sau).

Mô tả nhanh cách hoạt động của `TableConverter::convert(vector<T> items)`:

-   Bước 0: Khởi tạo `Converter` với `headers, columnSizes, separator` (gọi từ bên ngoài) với các giá trị `columnSizes` thỏa điều kiện.

-   Bước 1: Gọi hàm `prepareTableStructure()`, hàm này xây dựng nên các cột `headers` bằng `std::vformat`. Đồng thời, tạo `vector<string> _columnFormats` là mảng các chuỗi có kiểu như sau: `"{:>x}"`.

-   Bước 2: Khởi tạo `RowConverter` với `_columnFormats` được tạo thành từ Bước 1.

-   Bước 3: Với mỗi giá trị `item` trong mảng dữ liệu, sẽ được xây dựng thành một hàng trong bảng bằng cách gọi `RowConverter::convert(item)`.

-   Bước 3.1: Cài đặt các dữ liệu của hàng theo từng cột bằng hàm `setRowData(item)`.

-   Bước 3.2: Tạo lần lượt từng cột dữ liệu bằng cách sử dụng: `vformat(_columnFormats[i], make_format_args(_rowData[i]))`

-   Bước 4: Trả về bảng kết quả.

Cách sử dụng `Class TableConverter`, ví dụ với `ProposalToTableConverter`:

```cpp
class ProposalToTableConverter : public TableConverter<IProposal*> {
public:
	ProposalToTableConverter() : TableConverter<IProposal*>() {}
	ProposalToTableConverter(TableFormat config) :TableConverter<IProposal*>(config) {}
};

vector<string> ProposalToTableConverter::RowConverter::setRowData(IProposal* item){
    // Snippet to get a row data column by column
}

```

Có thể thấy, với `Class TableConverter` như thế này, có thể giảm tải hầu hết các công việc khi muốn in ra các loại bảng khác nhau. Việc chúng ta cần làm duy nhất là tạo một `Class` mới kế thừa `TableConverter<T>` và định nghĩa những dữ liệu sẽ được in ra bằng hàm `RowConverter::setRowData<T>`. `Một lần làm sướng cả đời`.

Để thấy chi tiết kết quả, thầy có thể chạy thử hàm main trong chương trình của em. Hai `Class` `ProposalToTableConverter` và `TourProposalToTableConverter` chỉ khác nhau `headers, columnSizes, setRowData()`.

## Version 4

Đây là Version của tương lai =)))). Khi mà em hết lười và trả được hết đống Technical Debt mà em để lại.

Các Technical Debt cần trả:

-   Sử dụng `smart_pointer` thay cho con trỏ thông thường.

-   Wrap `String` và `Vector`.

-   Catch hết `Exception`. Hiện tại thì trong code em không hề có 1 dòng `try...catch...` nào...

-   Document lại các hàm trong Code.

## Tổng kết

Ban đầu em chỉ định giải thích sơ sài những gì em làm. Nhưng mà càng viết càng thấy nói sơ sài thì không rõ được ý tưởng. Viết một hồi em nhận ra là có khi thầy đọc code của em lại hiểu hơn cả khi đọc những gì em viết =)))). Em đã cố gắng hết sức hoàn thành những gì em nghĩ sớm nhất có thể để thầy chấm chung với các bạn, nhưng mà đã mất tận 3 ngày, nên em đã không kịp trả đống nợ em nói trên.

Nhưng mà nếu thầy đọc tới đây thì em cảm ơn thầy rất nhiều vì đã đọc code của em, mặc dù thầy không có trách nhiệm với em trong phần thực hành. Thầy dạy rất hay, nên gần như lúc nào chào thầy cả lớp cũng vỗ tay. Em có dự định học C# nên em sẽ đăng kí lớp lập trình Windows, mong là được học thầy lần nữa. Em cảm ơn thầy.
