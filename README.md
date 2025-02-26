Magnetostriction refers to the phenomenon where ferromagnetic materials experience a change in shape or dimensions when subjected to a varying magnetic field. This effect arises due to the realignment of magnetic domains within the material in response to the oscillating magnetic field. When these materials resonate due to the oscillations, they generate mechanical vibrations that can propagate as acoustic waves, producing noise.

In the context of transformers, magnetostriction plays a significant role in the characteristic hum or buzzing sound often associated with their operation. The noise is primarily caused by the expansion and contraction of the core material as the magnetic field fluctuates with the alternating current (AC). This phenomenon not only indicates the normal operation of the transformer but can also provide diagnostic insights into its condition. For instance, the amplitude and frequency of the noise can help identify specific issues. An increase in noise levels may signal that the transformer is overloaded due to excessive current, while irregular or unusual noise patterns might indicate mechanical deformations, core vibrations, loose components, or failures in the electrical system, such as insulation breakdowns or winding faults.

To leverage this acoustic data for diagnostic purposes, it is essential to create a broad and diverse audio dataset to train a neural network using platforms like Edge Impulse. This training dataset will enable the neural network to accurately recognize and classify different types of transformer issues based on sound patterns.

In the initial phase, we are focusing on generating an audio dataset using a small transformer designed to step down voltage from 220V to 110V. This transformer will be intentionally overloaded with a resistive load to produce distinct sound patterns associated with stress and overloading. By collecting and analyzing these recordings, we aim to create a foundation for training a model that can eventually diagnose a wide range of transformer problems across various scenarios. This approach not only enhances predictive maintenance capabilities but also contributes to a more efficient and reliable electrical infrastructure.
