if "__main__" == __name__:

    from orion.client import get_experiment
    import plotly.express as px
    import os
    # Specify the database where the experiments are stored. We use a local PickleDB here.
    storage = storage = {
            "database": {
                "type": "mongodb",
                "name": 'orion_test',
                "host": os.environ['mongodbbURI']
            },
        }

    # Load the data for the specified experiment
    experiment = get_experiment("newScoring", storage=storage)
    fig = experiment.plot.parallel_coordinates(colorscale="YlOrRd")
    fig.write_html("colored1.html")

    fig.update_traces(overwrite=True, color_continuous_scale="RdBu")
    fig.write_html("colored2.html")


