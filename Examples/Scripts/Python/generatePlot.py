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
    experiment = get_experiment("newScoring", storage=storage)
    fig = experiment.plot.parallel_coordinates(colorscale="thermal")
    fig.write_html("colored.html")


