
class Node{
    int key;
    Node left, right;

    public Node(int value){
        key = value;
        left = right = null;
    }

    public void insert(int value){
        if(value > key){
            if(right == null) right = new Node(value);
            else right.insert(value);
        }else{
            if(left == null) left = new Node(value);
            else left.insert(value);
        }
    }

    public Node search(int value){
        if(left != null && key < value){
            if(left.key == value)
                return left;
            else return left.search(value);
        }
        else if(right != null){
            if(right.key == value)
                return right;
            else return right.search(value);
        }

        return null;
    }

    public void inorder(){
        if(left != null)
            left.inorder();
        System.out.println(key);
        if(right != null)
            right.inorder();
    }
}

public class BinaryTree {

    Node root;
    BinaryTree(int key){
        root = new Node(key);
    }

    BinaryTree(){
        root = null;
    }

    public void insert(int value){
        if(root == null){
            root = new Node(value);
        }else{
            root.insert(value);
        }
    }

    public Node search(int value){
        if(root != null){
            if(root.key == value)
                return root;
            return root.search(value);
        }
        return null;
    }

    public boolean remove(int value){
        Node tmp = search(value);
        if(tmp == null)
            return false;
        if(tmp.right != null){
            tmp.key = tmp.right.key;
            tmp.right = tmp.right.right;
        }else if(tmp.left != null){
            tmp.key = tmp.left.key;
            tmp.left = tmp.left.left;
        }else{
            //is a leaf
            tmp = null;
        }

        return true;
    }

    public void traverseInorder(){
        if(root != null) root.inorder();
    }


    public static void main(String []args){
        BinaryTree tree = new BinaryTree();

        for(int i = 0 ; i < 100; i++){
            tree.insert(i);
        }

        tree.traverseInorder();

        Node tmp = tree.search(5);

        System.out.println(tmp.key);

        System.out.println(tree.remove(5));
        System.out.println(tree.search(5));
        System.out.println(tree.search(6));
    }
    
}
