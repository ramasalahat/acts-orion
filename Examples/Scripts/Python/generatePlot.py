if "__main__" == __name__:

    from orion.client import get_experiment
    import plotly.express as px
    import os

    # Specify the database where the experiments are stored. We use a local PickleDB here.
    storage = storage = {
            "database": {
                "type": "mongodb",
                "name": 'orion_test',
                "host": os.environ['mongodbURI']
            },
        }

    # Load the data for the specified experiment
    experiment = get_experiment("experiment_random", storage=storage)

    df = experiment.to_pandas()

    best = df.iloc[df.objective.idxmin()]
    print(best)

    fig = experiment.plot.parallel_coordinates(colorscale="Plotly3")
    fig.update_yaxes(range=[0.025, 0.161])
    fig.update(layout_yaxis_range = [0.025, 0.161])
    fig.update_layout(yaxis_range=[0.025, 0.161])


    fig.write_html("colored.html")


