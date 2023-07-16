type str {
    let data: char[];
    let len: int;
    func pub static init(s: char[]): str {
        let this: str;
        this.data = s;
        this.len = 0;
        while (s[this.len])
            this.len++;
        return this;
    }
    func pub get(): char[] {
        return data;
    }
}
type BST<T: int> {
    let data: T;
    cons Leaf;
    cons Tree(l: BST<T>, r: BST<T>);
}

func main(): i32 {
    let s: *str = new(str);
    *s = str.init("hello world\n");
    printf(s.get());
    return 0;
}
