import matplotlib.pyplot as plt
from matplotlib import ticker


def read_data(file_path):
    x_values = []
    y_values = []
    with open(file_path, 'r') as file:
        for line in file:
            if line.strip():  # Avoid empty lines
                x, y = line.strip().split(';')
                x_values.append(float(x))
                y_values.append(float(y))
    return x_values, y_values


def plot_data(x1, y1, x2, y2):
    fig, ax = plt.subplots()
    ax.plot(x1, y1, label='Recurrence', markersize=1)
    ax.plot(x2, y2, label='While', markersize=1)
    ax.yaxis.set_major_formatter(ticker.ScalarFormatter(useMathText=True))
    fig.savefig("wykres.jpg", dpi=1000)


if __name__ == '__main__':
    file_path1 = 'data_recurrence.csv'
    x_values_recurrence, y_values_recurrence = read_data(file_path1)

    file_path2 = 'data_while.csv'
    x_values_while, y_values_while = read_data(file_path2)

    plot_data(x_values_recurrence, y_values_recurrence, x_values_while, y_values_while)
