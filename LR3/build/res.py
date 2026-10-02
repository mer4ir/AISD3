import matplotlib.pyplot as plt
import numpy as np
import os

def ensure_directory(directory):
    """Создает директорию, если она не существует"""
    if not os.path.exists(directory):
        os.makedirs(directory)
        print(f"Создана папка: {directory}")

def read_stats_file_simple(filename):
    """Простое чтение файла со статистикой"""
    with open(filename, 'r') as f:
        lines = [line.strip() for line in f if line.strip()]
    
    # Размеры массивов
    sizes = [1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 25000, 50000]
    
    # Разделяем на 3 группы
    comparisons_avg = []
    copies_avg = []
    comparisons_sorted = []
    copies_sorted = []
    comparisons_reverse = []
    copies_reverse = []
    
    for i, line in enumerate(lines[:36]):  # Берем только первые 36 строк
        try:
            comp, copy = map(int, line.split())
            
            if i < 12:  # Средний случай
                comparisons_avg.append(comp)
                copies_avg.append(copy)
            elif i < 24:  # Отсортированный
                comparisons_sorted.append(comp)
                copies_sorted.append(copy)
            elif i < 36:  # Обратно отсортированный
                comparisons_reverse.append(comp)
                copies_reverse.append(copy)
                
        except ValueError:
            # Добавляем нули для пропущенных данных
            if i < 12:
                comparisons_avg.append(0)
                copies_avg.append(0)
            elif i < 24:
                comparisons_sorted.append(0)
                copies_sorted.append(0)
            elif i < 36:
                comparisons_reverse.append(0)
                copies_reverse.append(0)
    
    # Убедимся, что у нас есть все 12 значений для каждого случая
    while len(comparisons_avg) < 12:
        comparisons_avg.append(0)
        copies_avg.append(0)
    
    while len(comparisons_sorted) < 12:
        comparisons_sorted.append(0)
        copies_sorted.append(0)
    
    while len(comparisons_reverse) < 12:
        comparisons_reverse.append(0)
        copies_reverse.append(0)
    
    return sizes, (comparisons_avg, copies_avg), (comparisons_sorted, copies_sorted), (comparisons_reverse, copies_reverse)

def create_full_analysis(sizes, all_cases_data):
    """Все сортировки и все случаи на одном большом графике"""
    fig, axes = plt.subplots(3, 3, figsize=(18, 12))
    fig.suptitle('ПОЛНЫЙ АНАЛИЗ АЛГОРИТМОВ СОРТИРОВКИ\nСравнения и копирования для всех случаев', 
                 fontsize=16, fontweight='bold', y=0.98)
    
    cases = ['Средний случай', 'Отсортированный', 'Обратный']
    sort_names = ['Bubble Sort', 'Comb Sort', 'Heap Sort']
    colors = ['red', 'green', 'blue']
    
    for case_idx, case_name in enumerate(cases):
        for sort_idx, sort_name in enumerate(sort_names):
            ax = axes[case_idx, sort_idx]
            comparisons, copies = all_cases_data[case_idx][sort_name]
            
            # Сравнения (сплошная линия)
            ax.plot(sizes, comparisons[:len(sizes)], 'o-', color=colors[sort_idx], 
                   label='Сравнения', linewidth=2, markersize=4)
            
            # Копирования (пунктирная линия)
            ax.plot(sizes, copies[:len(sizes)], 's--', color=colors[sort_idx], 
                   label='Копирования', linewidth=2, markersize=4)
            
            # Заголовки
            if case_idx == 0:
                ax.set_title(f'{sort_name}', fontweight='bold')
            if sort_idx == 0:
                ax.set_ylabel(f'{case_name}\nКоличество операций')
            
            ax.set_xlabel('Размер массива')
            ax.grid(True, alpha=0.3)
            ax.legend(fontsize=9)
            ax.ticklabel_format(style='sci', axis='y', scilimits=(0,0))
    
    plt.tight_layout(rect=[0, 0, 1, 0.96])
    return fig

def main():
    print("=" * 60)
    print("СОЗДАНИЕ ГРАФИКА ПОЛНОГО АНАЛИЗА")
    print("=" * 60)
    
    # Переходим в директорию скрипта
    script_dir = os.path.dirname(os.path.abspath(__file__))
    os.chdir(script_dir)
    print(f"Рабочая директория: {script_dir}")
    print()
    
    # Создаем папку для графиков
    graphs_dir = os.path.join(script_dir, "graphs")
    ensure_directory(graphs_dir)
    
    # Проверяем наличие файлов
    required_files = ['res1.txt', 'res2.txt', 'res3.txt']
    for file in required_files:
        if not os.path.exists(file):
            print(f"ОШИБКА: Файл '{file}' не найден!")
            print("Убедитесь, что:")
            print("1. C++ программа была выполнена")
            print(f"2. Файл находится в папке: {script_dir}")
            return
    
    print("✓ Все файлы найдены\n")
    print("Чтение данных...")
    
    # Читаем данные
    sizes, bubble_avg, bubble_sorted, bubble_reverse = read_stats_file_simple('res1.txt')
    _, comb_avg, comb_sorted, comb_reverse = read_stats_file_simple('res2.txt')
    _, heap_avg, heap_sorted, heap_reverse = read_stats_file_simple('res3.txt')
    
    # Подготавливаем данные для графика
    all_cases_data = [
        {  # Средний случай
            'Bubble Sort': bubble_avg,
            'Comb Sort': comb_avg,
            'Heap Sort': heap_avg
        },
        {  # Отсортированный массив
            'Bubble Sort': bubble_sorted,
            'Comb Sort': comb_sorted,
            'Heap Sort': heap_sorted
        },
        {  # Обратно отсортированный массив
            'Bubble Sort': bubble_reverse,
            'Comb Sort': comb_reverse,
            'Heap Sort': heap_reverse
        }
    ]
    
    # Создаем и сохраняем график
    print("\nСоздание графика полного анализа...")
    fig = create_full_analysis(sizes, all_cases_data)
    
    # Сохраняем график
    filename = "full_analysis.png"
    filepath = os.path.join(graphs_dir, filename)
    plt.savefig(filepath, dpi=300, bbox_inches='tight')
    print(f"✓ График сохранен: {filepath}")
    
    # Показываем график
    plt.show()
    
    print("\n" + "=" * 60)
    print("✓ ГРАФИК УСПЕШНО СОХРАНЕН!")
    print(f"✓ Файл: {filepath}")
    print("=" * 60)

if __name__ == "__main__":
    # Настройки графиков
    plt.rcParams['figure.figsize'] = (12, 8)
    plt.rcParams['font.size'] = 11
    plt.rcParams['axes.titlesize'] = 12
    plt.rcParams['axes.labelsize'] = 11
    plt.rcParams['legend.fontsize'] = 10
    plt.rcParams['savefig.dpi'] = 300
    
    # Используем стиль по умолчанию
    plt.style.use('default')
    
    main()