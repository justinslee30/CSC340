import java.util.*;

//generic class used to show sorting algorithms
//using T as a generic type
public class Sorting<T extends Comparable<T>> {
    static int numCallsMerge = 0;
    static int numCompMerge = 0;
    static int numAddsMerge = 0;
    static int numCallsQuick = 0;
    static int numCompQuick = 0;
    static int numSwapsQuick = 0;
    private Vector<T> entries;

    //setter function for Sorting class, creates a copy of the vector and makes it equal to that
    //allows for easy reset
    public void setEntries(Vector<T> entries) {
        this.entries = (Vector<T>) entries.clone();
    }

    //getter function for Sorting class
    public Vector<T> getEntries() {
        return this.entries;
    }

    //selection sort
    public Vector<T> selectionSort() {
        Vector<T> selectSortV = getEntries();
        int numberOfComparisons = 0;
        int numberOfSwaps = 0;
        int minIndex;
        int swapIndex;
        //iterate through loop, setting the pivot index
        for (int i = 0; i < selectSortV.size(); i++)
        {
            swapIndex = i;
            minIndex = i;
            //using pivot index, check with rest of array after the pivot index
            for (int j = i; j < selectSortV.size(); j++)
            {
                numberOfComparisons++;
                //get the index of the minimum value
                if (selectSortV.get(j).compareTo(selectSortV.get(minIndex)) < 0)
                {
                    minIndex = j;
                }
            }
            //swap the values at the pivot index with the minimum value
            Collections.swap(selectSortV,swapIndex,minIndex);
            numberOfSwaps++;
            System.out.println("Number of Comparisons: " + numberOfComparisons);
            System.out.println("Number of Swaps: " + numberOfSwaps);
            System.out.println("Elements are " + selectSortV);
        }

        return selectSortV;
    }
    //insertion sort
    public Vector<T> insertionSort() {
        Vector<T> insertSortV = new Vector<>();
        int numberOfComparisons = 0;
        int numberOfMoves = 0;
        //add the value at the index i to the insertSortV
        for (int i = 0; i < entries.size(); i++)
        {
            numberOfMoves++;
            insertSortV.add(entries.get(i));
            //for the first entry, this never enters
            //for after the first entry, enters and compares with value before it, if less, than swaps the two
            for (int j = i; j > 0; j--)
            {
                numberOfComparisons++;
                if (insertSortV.get(j).compareTo(insertSortV.get(j-1)) < 0)
                {
                    Collections.swap(insertSortV,j,j-1);
                }
            }
            System.out.println("Number of Comparisons: " + numberOfComparisons);
            System.out.println("Number of Swaps: " + numberOfMoves);
            System.out.println("Elements are "+ insertSortV);
        }

        return insertSortV;
    }
    //shell sort
    public Vector<T> shellSort(){
        Vector<T> shellSortV = getEntries();
        int entries_size = shellSortV.size();
        int numberOfComparisons = 0;
        int numberOfSwaps = 0;
        //split the subarrays by 2 every iteration
        for (int i = entries_size/2; i > 0; i = i/2)
        {
            //compares the number at i until end with all numbers before it given some interval i
            for (int j = i; j < entries_size; j++)
            {
                int k = 1;
                //compares it with all numbers before it given some interval i, while loop ensures does not index below 0
                while (j - (k * i) >= 0)
                {
                    numberOfComparisons++;
                    if (shellSortV.get(j-((k-1)*i)).compareTo(shellSortV.get(j - (k * i))) < 0)
                    {
                        numberOfSwaps++;
                        Collections.swap(shellSortV, j-((k-1)*i), j - (k * i));
                    }
                    k++;
                }
            }
            System.out.println("Number of Comparisons: " + numberOfComparisons);
            System.out.println("Number of Swaps: " + numberOfSwaps);
            System.out.println("Elements are "+ shellSortV);
        }
        return shellSortV;
    }
    //bubble sort
    public Vector<T> bubbleSort() {
        Vector<T> bubbleSortV = getEntries();
        int numberOfComparisons = 0;
        int numberOfSwaps = 0;
        boolean sorted = false;
        //while sorted is not true
        while (!sorted)
        {
            //assume sorted is true at beginning of pass
            sorted = true;
            //start at zero and bubble through
            for (int i = 0; i < bubbleSortV.size()-1; i++)
            {
                numberOfComparisons++;
                //if there is a swap, then vector not sorted yet
                if (bubbleSortV.get(i).compareTo(bubbleSortV.get(i+1)) > 0)
                {
                    //change sorted to false if a swap occurs
                    numberOfSwaps++;
                    Collections.swap(bubbleSortV,i,i+1);
                    sorted = false;
                }
            }
            System.out.println("Number of Comparisons: " + numberOfComparisons);
            System.out.println("Number of Swaps: " + numberOfSwaps);
            System.out.println("Elements are "+ bubbleSortV);
        }
        return bubbleSortV;
    }
    //merge sort
    public Vector<T> mergeSort(int l, int r){
        numCallsMerge++;
        Vector<T> mergeSortV = getEntries();
        if (l < r)
        {
            int mid = l + (r-l)/2;
            mergeSort(l,mid);
            mergeSort(mid + 1, r);
            merge(mergeSortV,l,mid,r);
        }
        return mergeSortV;
    }
    //merge sort helper - merge
    public void merge(Vector<T> vec, int l, int m, int r){
        //find size of two subarrays to be merged
        int n1 = m - l + 1;
        int n2 = r - m;
        //create temporary arrays to hold the values
        Vector<T> left = new Vector<>();
        Vector<T> right= new Vector<>();
        //copy the values into the temporary arrays
        for (int i = 0; i < n1; i++)
        {
            left.add(vec.get(l+i));
        }
        for (int j = 0; j < n2; j++)
        {
            right.add(vec.get(m+j+1));
        }
        //add the sorted values to vec
        int k = l;
        int i = 0;
        int j = 0;
        while (i < n1 && j < n2)
        {
            numCompMerge++;
            numAddsMerge++;
            if (left.get(i).compareTo(right.get(j)) < 0)
            {
                vec.set(k, left.get(i));
                i++;
            }
            else
            {
                vec.set(k,right.get(j));
                j++;
            }
            k++;
            System.out.println("Number of Comparisons: " + numCompMerge);
            System.out.println("Number of Adds: " + numAddsMerge);
            System.out.println("Elements are "+ vec);
        }
        //add remaining elements of left and right
        while (i < n1)
        {
            vec.set(k,left.get(i));
            i++;
            k++;
            numAddsMerge++;
            System.out.println("Number of Comparisons: " + numCompMerge);
            System.out.println("Number of Swaps: " + numAddsMerge);
            System.out.println("Elements are "+ vec);
        }
        while (j < n2)
        {
            vec.set(k,right.get(j));
            j++;
            k++;
            numAddsMerge++;
            System.out.println("Number of Comparisons: " + numCompMerge);
            System.out.println("Number of Swaps: " + numAddsMerge);
            System.out.println("Elements are "+ vec);
        }
    }
    //quick sort
    public Vector<T> quickSort(int l, int r){
        numCallsQuick++;
        Vector<T> quickSortV = getEntries();
        if (l < r)
        {
            int pi = partition(quickSortV, l, r);
            quickSort(l, pi - 1);
            quickSort(pi + 1, r);
        }
        return quickSortV;
    }
    //quick sort helper - partition
    int partition(Vector<T> vec, int l, int r){
        int pivot_new_index = l-1;
        for (int j = l; j <= r - 1; j++)
        {
            numCompQuick++;
            if (vec.get(r).compareTo(vec.get(j)) > 0 && j != l)
            {
                pivot_new_index++;
                Collections.swap(vec,j,pivot_new_index);
                numSwapsQuick++;
                System.out.println("Number of Comparisons: " + numCompQuick);
                System.out.println("Number of Swaps: " + numSwapsQuick);
                System.out.println("Elements are "+ vec);
            }
            else if (vec.get(r).compareTo(vec.get(j)) > 0)
            {
                pivot_new_index++;
            }
        }
        pivot_new_index++;
        Collections.swap(vec,pivot_new_index,r);
        System.out.println("Number of Comparisons: " + numCompQuick);
        System.out.println("Number of Swaps: " + numSwapsQuick);
        System.out.println("Elements are "+ vec);
        return pivot_new_index;
    }
    //radix sort
    //tree sort
    //heap sort
    //binary search

    public static void main(String[] arg)
    {
        Sorting sorting_exercise = new Sorting<>();
        Vector<Integer> dataset = new Vector<>();
        Random rand = new Random();
        int upperbound = 100;
        for (int i = 0; i < 9; i++)
        {
            dataset.add(rand.nextInt(upperbound));
        }
        sorting_exercise.setEntries(dataset);
        System.out.println("Elements are " + sorting_exercise.getEntries());
        System.out.println("--------Selection Sort--------");
        Vector seS = sorting_exercise.selectionSort();
        sorting_exercise.setEntries(dataset);
        System.out.println("--------Insertion Sort--------");
        Vector inS = sorting_exercise.insertionSort();
        sorting_exercise.setEntries(dataset);
        System.out.println("--------Shell Sort--------");
        Vector shS = sorting_exercise.shellSort();
        sorting_exercise.setEntries(dataset);
        System.out.println("--------Bubble Sort--------");
        Vector bbS = sorting_exercise.bubbleSort();
        sorting_exercise.setEntries(dataset);
        System.out.println("--------Merge Sort--------");
        Vector meS = sorting_exercise.mergeSort(0,sorting_exercise.getEntries().size()-1);
        sorting_exercise.setEntries(dataset);
        System.out.println("--------Quick Sort--------");
        Vector qsS = sorting_exercise.quickSort(0,sorting_exercise.getEntries().size()-1);
        sorting_exercise.setEntries(dataset);
    }
}
